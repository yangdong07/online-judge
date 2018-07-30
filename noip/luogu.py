import os
import sys
import shutil
import traceback
import time
import warnings

import argparse

import urllib.parse

from collections import defaultdict, OrderedDict
from pprint import pprint

try:
    #python2
    from urllib import urlencode, urljoin
except ImportError:
    #python3
    from urllib.parse import urlencode, urljoin

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


'''
{ "_id" : "省选/NOI-", "count" : 936 }
{ "_id" : "普及/提高-", "count" : 475 }
{ "_id" : "尚无评定", "count" : 450 }
{ "_id" : "普及+/提高", "count" : 309 }
{ "_id" : "入门难度", "count" : 113 }
{ "_id" : "NOI/NOI+/CTSC", "count" : 281 }
{ "_id" : "提高+/省选-", "count" : 903 }
{ "_id" : "普及-", "count" : 315 }
'''
LEVELS = {
    '尚无评定': 0,
    '入门难度': 1,
    '普及-': 2,
    '普及/提高-': 3,
    '普及+/提高': 4,
    '提高+/省选-': 5,
    '省选/NOI-': 6,
    'NOI/NOI+/CTSC': 7,
}


def init_db():
    client = MongoClient('localhost', 27017)
    client.spider.drop_collection(COLLECTION_NAME)
    client.spider.create_collection(COLLECTION_NAME)
    collection = client.spider[COLLECTION_NAME]
    collection.create_index("index", unique=True)
    return collection


def get_db():
    client = MongoClient('localhost', 27017)
    return client.spider[COLLECTION_NAME]


def init_web_driver():
    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--window-size=1920x1080")

    driver = webdriver.Chrome(WEB_DRIVER_PATH, chrome_options=chrome_options)
    return driver


# parse all problems page
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


# get all problems
def init_all_problems():
    driver = init_web_driver()

    # parse_page(driver.page_source)
    collection = get_db()

    next_link = PROBLEMS_PAGE_URL(1)
    while next_link:
        driver.get(next_link)
        time.sleep(5)
        problems, next_link = extract_problems_from_page(driver.page_source)
        print(next_link)
        # break

        for problem in problems:
            collection.update_one({'index': problem['index']}, {'$set': problem}, upsert=True)


def update_topics():
    driver = init_web_driver()
    driver.get("https://luogu.com/problemset/all/")
    time.sleep(5)

    # expand topic
    driver.find_element_by_css_selector('#expand-topic > div.btn').click()
    topic_links = driver.find_element_by_css_selector('#current-topic-tags').find_elements_by_tag_name('a')

    # get all topic link
    topic_link_dict = dict()
    for topic_link in topic_links:
        link = topic_link.get_attribute('href')
        topic = topic_link.find_element_by_css_selector('span.text-sm').text
        topic_link_dict[link] = topic

    # get url and parse topics
    problem_topics = dict()
    for link, topic in topic_link_dict.items():
        driver.get(link)
        time.sleep(1)

        problems = parse_topic_page(driver.page_source)

        for index in problems:
            if index not in problem_topics:
                problem_topics[index] = set()
            problem_topics[index].add(topic)

    pprint(problem_topics)

    luogu = get_db()
    for index, topics in problem_topics.items():
        luogu.update_one({'index': index}, {'$set': {'tags': list(topics)}})

    return problem_topics


def update_detail(indices):

    driver = init_web_driver()
    luogu = get_db()

    for index in indices:
        problem = luogu.find_one({'index': index})
        if not problem:
            continue
        print('update index: ', index)
        problem_link = problem['problem_link']
        driver.get(problem_link)
        driver.implicitly_wait(10)
        try:
            content = driver.find_elements_by_css_selector('div.question-content > div')[1].get_attribute('innerHTML')
            luogu.update_one({'index': problem['index']}, {'$set': {'description': content, 'status': 'ok'}})
        except:
            luogu.update_one({'index': problem['index']}, {'$set': {'status': 'error'}})

    driver.close()


def search_solutions_and_codes(path='./solutions'):
    # search solutions
    solutions = {}
    for file_name in os.listdir(path):
        file_path = os.path.join(path, file_name)
        if os.path.isfile(file_path) and file_name.endswith('.md'):
            index = file_name.split('.')[0]
            solutions[index] = file_path

    # search code
    code_candidates = {'python': '.py'}
    code_links = defaultdict(dict)
    for code, suffix in code_candidates.items():
        code_path = './' + code
        if os.path.exists(code_path):
            for file_name in os.listdir(code_path):
                file_path = os.path.join(code_path, file_name)
                if os.path.isfile(file_path) and file_name.endswith(suffix):
                    index = file_name.split('.')[0]
                    code_links[index][code] = file_path
    return solutions, code_links


def get_tag_problems(problems):
    problems = {p['index']: p for p in problems}

    topics = defaultdict(list)
    for index, problem in problems.items():
        if 'tags' not in problem:
            topics['other'].append(problem)
        else:
            tags = problem['tags']
            for tag in tags:
                topics[tag].append(problem)

    tag_problems = OrderedDict()
    for tag in sorted(topics.keys()):
        tag_problems[tag] = topics[tag]
    return tag_problems


def generate_table(problems):
    headers = ['#', 'Title', 'Algorithm Tags', 'Tags', 'Solution', 'Code']
    markers = [':---:' for _ in headers]
    markers[1] = '---'   # Title
    headers = [''] + headers + ['']
    markers = [''] + markers + ['']

    table = list()
    table.append("|".join(headers))
    table.append("|".join(markers))

    for problem in problems:
        index = problem['index']
        marked = '💎' if problem['marked'] else ''
        problem_link = '[%s](%s)%s' % (problem['title'].replace('|', '-'), problem['problem_link'], marked)

        algorithm_tags = problem.get('algorithm_tags', [])
        tags = [t for t in problem.get('tags', {}).values() if t not in algorithm_tags]

        solution_link = ''
        code_link = ''
        content = [
            '',
            index,
            problem_link,
            ','.join(algorithm_tags),
            ','.join(tags),
            solution_link,
            code_link,
            '',
        ]
        table.append("|".join(content))

    return table


def generate_tables():
    db = get_db()
    levels = db.aggregate([{"$group": {"_id": "$level", "count": {"$sum": 1}}}])
    levels = [l['_id'] for l in levels]

    for l in levels:
        if l not in LEVELS:
            raise Exception('level not match, please check it, %s' % l)

    levels.sort(key=lambda l: LEVELS[l])

    pprint(levels)

    for level in levels:
        problems = db.find({'level': level})
        file_path = os.path.join('./index', '%s.%s.md' % (LEVELS[level], level.replace('/', '\\')))
        print(file_path)
        with open(file_path, 'w') as f:
            f.write('\n## %s\n\n' % level)
            for line in generate_table(problems):
                f.write(line + '\n')

    #
    # solved_count = defaultdict(int)
    # for tag, problems in tag_problems.items():
    #     solved = [p for p in problems if p['index'] in solutions]
    #     solved_count[tag] = len(solved)
    #
    # headers = ['Topic', 'Total', 'Solved', 'Progress']
    # markers = ['-'*len(h) for h in headers]
    # markers[-1] = markers[-1] + ':'
    # headers = [''] + headers + ['']
    # markers = [''] + markers + ['']
    #
    # table = list()
    # table.append("|".join(headers))
    # table.append("|".join(markers))
    #
    # # tag tables
    # for tag in tag_problems:
    #     tag_link = urllib.parse.quote(os.path.join('./topics', tag + '.md'))
    #     count = len(tag_problems[tag])
    #     # print
    #     solved = solved_count[tag]
    #     progress = 100.0 * solved / count
    #     content = [
    #         '',
    #         '[%s](%s)' % (tag, tag_link),
    #         str(count),
    #         # problem_tags,
    #         str(solved),
    #         '%5.2f %%' % progress,
    #         '',
    #     ]
    #     table.append('|'.join(content))
    #
    # total = luogu.find().count()
    # solved = len(solutions.keys())
    # content = [
    #     '',
    #     'Total',
    #     str(total),
    #     # problem_tags,
    #     str(solved),
    #     '%.2f %%' % (100.0 * solved / total),
    #     '',
    # ]
    # table.append('|'.join(content))
    #
    # with open('index.md', 'w') as f:
    #     f.write('\n## luogu\n\n')
    #     f.write('\n'.join(table))


def generate_template(index):
    luogu = get_db()
    problem = luogu.find_one({'index': index})
    if not problem:
        raise Exception('problem %s not found' % index)

    title = '%s. %s' % (index, problem['title'])
    md_file = title + '.md'
    py_file = title + '.py'

    if os.path.exists(md_file):
        warnings.warn('Be careful!!! Overwriting %s' % md_file)
        time.sleep(1)

    # TODO: maybe unlock someday, if i'm rich.
    locked = problem.get('locked')
    if locked:
        raise Warning('The Problem "%s. %s" is Locked, You should subscribe to unlock' % (index, problem['title']))

    description = problem.get('description')

    if not description:
        warnings.warn('No Description here, need fetch from luogu')
        update_detail([index])

        # re get the problem
        problem = luogu.find_one({'index': index})
        if not problem:
            raise Exception('problem %s not found' % index)
        if problem['status'] != 'ok':
            pprint(problem)
            raise Exception('problem %s is not ok' % index)
        if not problem.get('description'):
            raise Exception('no description here, please check it: %s' % problem['problem_link'])

    abstract = ''
    topics = problem.get('tags')
    if topics:
        abstract = ', '.join(map(lambda x: '**' + x + '**', topics)) + '    '

    label = labels.get(problem['label'], '💔')
    abstract += '[%s](%s)' % (label, problem['problem_link']) + '    '
    if problem.get('solution_link'):
        abstract += '\t[💡](%s)' % problem['solution_link']

    # be careful here, be careful about the relative path
    code_link = '[Code](../python/%s)' % urllib.parse.quote(py_file)

    markdown = html2markdown(problem['description'])

    with open(md_file, 'w') as f:
        f.write('### %s\n\n' % md_file[:-3])
        # write topics
        f.write('%s\n\n' % abstract)
        f.write('#### Description\n\n')
        f.write(markdown)
        f.write('\n\n#### Analysis\n\n')
        f.write('#### %s\n\n' % code_link)

    # generate python empty file
    if not os.path.exists(py_file):
        with open(py_file, 'w') as f:
            f.write('\n\n# %s\n' % py_file[:-3])
            f.write('# %s\n\n' % problem['problem_link'])


def solved_and_commit(index):
    luogu = get_db()
    problem = luogu.find_one({'index': index})
    if not problem:
        raise Exception('problem %s not found' % index)

    title = '%s. %s' % (index, problem['title'])
    files = [title + '.md', title + '.cpp']

    # move files
    to_move = {}
    path_map = {'cpp': 'cpp', 'md': 'solutions'}
    for f in files:
        if not os.path.exists(f):
            warnings.warn('solution file <%s> not exists' % f)
            continue

        suffix = f.rsplit('.', 1)[-1]
        if suffix in path_map:
            path = os.path.join(path_map[suffix], f)
            to_move[f] = path
        else:
            warnings.warn('<%s> stay here' % f)

    print('Plan to Move:\n')
    for src, dst in to_move.items():
        print('\t %s ---> %s' % (src, dst))
    input('\nReady to Move?')

    for src, dst in to_move.items():
        shutil.move(src, dst)

    # udpate readme and tables
    generate_readme()
    generate_tables_by_tag()

    # git commit and push
    git = Repo('.').git
    print(git.add('.'))
    print(git.status())

    default_summary = '%s, Solved' % title
    commit = input('\nCheck git status, and Input Summary: [%s]\n' % default_summary)
    commit = commit or default_summary
    print(git.commit('-m', commit))

    input('Ready to Push?')
    print(git.push())


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command')

    parser_init = subparsers.add_parser('init', help='init db and init all problems')
    parser_generate = subparsers.add_parser('generate', help='generate readme or solution template')

    options_init = parser_init.add_mutually_exclusive_group()
    options_init.add_argument('--db', action='store_true')
    options_init.add_argument('-p', '--problems', action='store_true')

    options_generate = parser_generate.add_mutually_exclusive_group()
    options_generate.add_argument('-t', '--table', action='store_true')
    options_generate.add_argument('-i', '--index', nargs=1, help='generate template')
    options_generate.add_argument('-s', '--solved', nargs=1)

    args = parser.parse_args()

    # print(args)
    if args.command == 'init':
        if args.db:
            print('init database')
            init_db()
        elif args.problems:
            print('init problems')
            init_all_problems()
        else:
            parser_init.print_help()
    elif args.command == 'generate':
        if args.table:
            generate_tables()
        elif args.index:
            generate_template(args.index[0])
        elif args.solved:
            solved_and_commit(args.solved[0])
        else:
            parser_generate.print_help()
    else:
        parser.print_help()
