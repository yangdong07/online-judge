import os
import sys
import shutil
import traceback
import time
import warnings
import subprocess


import argparse

import urllib.parse

from collections import defaultdict, OrderedDict
from pprint import pprint

try:
    #python2
    from urllib import urlencode, urljoin, quote
except ImportError:
    #python3
    from urllib.parse import urlencode, urljoin, quote

import click
from yaml import load, dump
from git import Repo
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.action_chains import ActionChains

from pymongo import MongoClient


COLLECTION_NAME = 'luogu'
WEB_DRIVER_PATH = '/Users/yangdong/tools/chromedriver'

URL_JOIN = lambda path: urljoin('https://www.luogu.org/', path)
PROBLEMS_PAGE_URL = lambda page: "https://www.luogu.org/problemnew/lists?page=%s" % page


def init_db():
    client = MongoClient('localhost', 27017)
    client.spider.drop_collection(COLLECTION_NAME)
    client.spider.create_collection(COLLECTION_NAME)
    collection = client.spider[COLLECTION_NAME]
    collection.create_index("index", unique=True)
    return collection


def get_collection():
    client = MongoClient('localhost', 27017)
    return client.spider[COLLECTION_NAME]


def init_web_driver():
    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--window-size=1920x1080")

    driver = webdriver.Chrome(WEB_DRIVER_PATH, chrome_options=chrome_options)
    return driver


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


def extract_problem_article(page_content):
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
    driver = init_web_driver()

    # parse_page(driver.page_source)
    collection = get_collection()

    next_link = PROBLEMS_PAGE_URL(1)
    while next_link:
        driver.get(next_link)
        time.sleep(5)
        problems, next_link = extract_problems_from_page(driver.page_source)
        print(next_link)
        # break

        for problem in problems:
            collection.update_one({'index': problem['index']}, {'$set': problem}, upsert=True)


def update_problems_from_page(page):
    driver = init_web_driver()

    # parse_page(driver.page_source)
    collection = get_collection()

    next_link = PROBLEMS_PAGE_URL(page)
    driver.get(next_link)
    time.sleep(5)
    problems, next_link = extract_problems_from_page(driver.page_source)
    for problem in problems:
        collection.update_one({'index': problem['index']}, {'$set': problem}, upsert=True)


def update_problem_detail(problem_id, force_update=True):
    collection = get_collection()
    problem = collection.find_one({'index': problem_id})

    if not problem:
        raise Exception('problem <%s> not found' % problem_id)

    if not problem.get('raw_article'):
        driver = init_web_driver()
        driver.get(problem['problem_link'])
        driver.implicitly_wait(10)

        raw_article = extract_problem_article(driver.page_source)
        collection.update_one({'index': problem_id}, {'$set': {'raw_article': raw_article}})
    print(problem)
    problem = collection.find_one({'index': problem_id})
    test_examples = extract_test_examples_from_article(problem.get('raw_article'))
    print(test_examples)
    if test_examples:
        test_data_path = os.path.join('./data', '%s.yaml' % problem_id.lower())
        if not os.path.exists(test_data_path) or force_update:
            with open(test_data_path, 'w') as f:
                f.write(dump(test_examples))




def update_index_table():
    db = get_collection()
    levels = db.aggregate([{"$group": {"_id": "$level", "count": {"$sum": 1}}}])
    levels = [l['_id'] for l in levels]

    for l in levels:
        if l not in LEVELS:
            raise Exception('level not match, please check it, %s' % l)

    levels.sort(key=lambda l: LEVELS[l])

    pprint(levels)

    for level in levels:
        problems = db.find({'level': level})
        count = db.count({'level': level})
        solved = db.count({'level': level, 'solved': True})
        file_path = os.path.join('./index', '%s.%s.md' % (LEVELS[level], level.replace('/', '\\')))
        print(file_path)
        with open(file_path, 'w') as f:
            f.write('\n## %s\n\n' % level)
            f.write('%d / %d\n\n' % (solved, count))
            for line in generate_table(problems):
                f.write(line + '\n')


def generate_template(index, force_update=False):
    db = get_collection()
    problem = db.find_one({'index': index})
    if not problem:
        raise Exception('problem <%s> not found in db' % index)
    # print(problem)

    if force_update or not problem.get('raw_article'):
        update_problem_detail(index)

    problem = db.find_one({'index': index})

    # title is not regular
    solution_file = regular_file(index, problem['title'])
    code_file = index.lower() + '.cpp'

    if os.path.exists(solution_file):
        warnings.warn('Be careful!!! Overwriting %s' % solution_file)
        time.sleep(1)

    solution_template = make_solution_template(problem)
    cpp_template = make_solution_template(problem)

    with open(solution_file, 'w') as f:
        f.write(solution_template)

    # generate python empty file
    if not os.path.exists(code_file):
        # do not generate if exists
        with open(code_file, 'w') as f:
            f.write(cpp_template)


def compile_and_test(index):
    collection = get_collection()
    problem = collection.find_one({'index': index})

    code_file = index.lower() + '.cpp'
    output_bin = 'test.out'

    # compile
    result = subprocess.run('g++ -o {o} {src}'.format(src=code_file, o=output_bin), shell=True)
    if result.returncode != 0:
        exit(result.returncode)

    # test
    test_data_path = os.path.join('./data', '%s.yaml' % index.lower())
    if not os.path.exists(test_data_path):
        warnings.warn('no test case in this problem, please check it <%s>' % index)
        result = subprocess.run('./%s' % output_bin)
        return

    with open(test_data_path) as f:
        test_case = load(f)

    time_used = []
    for i, case in enumerate(reversed(test_case), 1):
        start_time = time.time()
        result = subprocess.run('./%s' % output_bin,
                                input=bytearray(case['i'], 'ascii'),
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)
        output = result.stdout.decode('ascii')
        error = result.stderr.decode('ascii')
        # sometimes there will have a '\n' at end;
        with open('test.output', 'w') as f:
            f.write(output)
        time_used.append(time.time() - start_time)
        if output != case['o'] and output != case['o'] + '\n':
            print('=' * 10 + ' Test Case #%s ' % i + '=' * 10)
            print('#input')
            print(case['i'])
            print('#expect')
            print(case['o'])
            print('#output')
            print(output)
            print(error)
            print('=' * 10 + ' Test Failed ' + '=' * 10)
            print('time used: %.3f s' % time_used[-1])
            exit(1)
    print(time_used)
    # for t in time_used:
    #     print('time used: %.3f s' % t)
    print('All Passed, Congratulations!')
