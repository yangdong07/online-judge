import os
import sys
import traceback
import time
import warnings

try:
    #python2
    from urllib import urlencode, urljoin, quote
except ImportError:
    #python3
    from urllib.parse import urlencode, urljoin, quote

from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.action_chains import ActionChains

from scripts.database import db_luogu, get_problem


WEB_DRIVER_PATH = '/Users/yangdong/tools/chromedriver'

URL_JOIN = lambda path: urljoin('https://www.luogu.org/', path)
PROBLEMS_PAGE_URL = lambda page: "https://www.luogu.org/problemnew/lists?page=%s" % page


chrome_driver = None


def get_web_driver():
    global chrome_driver
    if chrome_driver:
        return chrome_driver

    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--window-size=1920x1080")

    chrome_driver = webdriver.Chrome(WEB_DRIVER_PATH, chrome_options=chrome_options)
    return chrome_driver


def extract_problems_from_page(page_content):

    soup = BeautifulSoup(page_content, 'html.parser')
    table = soup.select_one('.lg-content-table-left')

    rows = table.select('.lg-table-row')

    count = 0
    problems = []
    for row in rows:
        try:
            marked = bool(row.select_one('.am-icon-diamond'))
            title_link = row.find_all('a')[-1]
            title = title_link.text.strip()
            problem_link = URL_JOIN(title_link['href'])
            problem_id = problem_link.rstrip('/').rsplit('/', 1)[-1]

            tags = row.select_one('span.lg-right').select('.am-badge')

            level = ''
            i = 0
            for tag in tags:
                i += 1
                if not tag.has_attr('data-tagid'):
                    level = tag.text.strip()
                    break
            algorithm_tags = list(map(lambda t: t.text.strip(), tags[i:]))
            tags = {t['data-tagid']: t.text.strip() for t in tags if t.has_attr('data-tagid')}

            count = count + 1
            print(count, problem_id, title)
            problems.append(dict(
                raw=str(row),
                index=problem_id,
                title=title,
                problem_link=problem_link,
                level=level,
                marked=marked,
                tags=tags,
                algorithm_tags=algorithm_tags
            ))

        except:
            print('Error parse: ', str(row))
            traceback.print_exc()

    pagination = soup.select_one('ul.am-pagination').find_all('a')

    next_page = next((p for p in pagination if p.text == '>'), None)
    next_link = ''
    if next_page and next_page.get('data-ci-pagination-page'):
        next_link = PROBLEMS_PAGE_URL(next_page.get('data-ci-pagination-page'))

    return problems, next_link


def extract_raw_article(page_content):
    soup = BeautifulSoup(page_content, 'html.parser')
    article = soup.select_one('.lg-article')
    return str(article)


def extract_test_examples_from_article(raw_article):
    article = BeautifulSoup(raw_article, 'html.parser')
    examples = article.select('.am-g > .am-g')
    test_examples = []
    for example in examples:
        code = example.find_all('pre')
        if len(code) == 2:
            test_examples.append({
                'i': code[0].text.strip(),
                'o': code[1].text.strip()
            })
        else:
            print(code)
    return test_examples


# get all problems
def get_all_problems():
    driver = get_web_driver()

    next_link = PROBLEMS_PAGE_URL(1)
    while next_link:
        driver.get(next_link)
        time.sleep(5)
        problems, next_link = extract_problems_from_page(driver.page_source)
        print(next_link)
        # break

        for problem in problems:
            db_luogu.update_one({'index': problem['index']}, {'$set': problem}, upsert=True)


def update_problems_from_page(page):
    driver = get_web_driver()

    next_link = PROBLEMS_PAGE_URL(page)
    driver.get(next_link)
    time.sleep(5)
    problems, next_link = extract_problems_from_page(driver.page_source)
    for problem in problems:
        db_luogu.update_one({'index': problem['index']}, {'$set': problem}, upsert=True)


def fetch_raw_problem(index, force=False):

    problem = get_problem(index)
    if not problem:
        raise Exception("problem <%s> not found" % index)

    if not force and problem.get('raw_article'):
        print('problem <%s> raw article exist' % index)
        test_examples = extract_test_examples_from_article(problem['raw_article'])
        print(test_examples)
        return

    driver = get_web_driver()
    driver.get(problem['problem_link'])
    driver.implicitly_wait(10)
    raw_article = extract_raw_article(driver.page_source)

    db_luogu.update_one({'index': problem['index']},
                        {'$set': {'raw_article': raw_article}})


