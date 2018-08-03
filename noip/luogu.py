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

    problem = collection.find_one({'index': problem_id})
    test_examples = extract_test_examples_from_article(problem.get('raw_article'))
    print(test_examples)
    if test_examples:
        test_data_path = os.path.join('./data', '%s.yaml' % problem_id.lower())
        if not os.path.exists(test_data_path) or force_update:
            with open(test_data_path, 'w') as f:
                f.write(dump(test_examples))


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
        marked = '⭐️' if problem['marked'] else ''
        # avoid '|' in markdown table
        problem_link = '%s[%s](%s)' % (marked, problem['title'].replace('|', '-'), problem['problem_link'])

        algorithm_tags = problem.get('algorithm_tags', [])
        tags = [t for t in problem.get('tags', {}).values() if t not in algorithm_tags]

        solution_link = ''
        code_link = ''
        if problem.get('solved'):
            solution_link = '[📜](../solutions/%s)' % quote('.'.join([index, problem['title'], 'md']))
            code_link = '[C++](../cpp/%s)' % quote('.'.join([index.lower(), 'cpp']))
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
        file_path = os.path.join('./index', '%s.%s.md' % (LEVELS[level], level.replace('/', '\\')))
        print(file_path)
        with open(file_path, 'w') as f:
            f.write('\n## %s\n\n' % level)
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

    solution_file = '%s.%s.md' % (index, problem['title'])
    code_file = index.lower() + '.cpp'

    if os.path.exists(solution_file):
        warnings.warn('Be careful!!! Overwriting %s' % solution_file)
        time.sleep(1)

    abstract = ''
    algorithm_tags = problem.get('algorithm_tags', [])
    tags = list(filter(lambda t: t not in algorithm_tags, problem.get('tags', {}).values()))
    if algorithm_tags:
        abstract = '算法标签: ' + ', '.join(map(lambda x: '**' + x + '**', algorithm_tags)) + '\n'

    if tags:
        abstract += '其他标签: ' + ', '.join(map(lambda x: '**' + x + '**', tags)) + '\n'

    # be careful here, be careful about the relative path
    code_file_path_will_be = '../cpp/%s' % quote(code_file)

    with open(solution_file, 'w') as f:
        f.write('### %s %s\n\n' % (index, problem['title']))
        # write topics
        f.write('%s\n\n' % abstract)
        f.write('#### Description\n\n')
        f.write('\n\n')
        f.write('\n\n#### Analysis\n\n')
        f.write('#### [Code](%s) \n\n' % code_file_path_will_be)

    # generate python empty file
    if not os.path.exists(code_file):
        with open(code_file, 'w') as f:
            f.write('// %s %s\n' % (index, problem['title']))
            f.write('// %s\n\n' % problem['problem_link'])


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
        return
    with open(test_data_path) as f:
        test_case = load(f)

    for i, case in enumerate(reversed(test_case), 1):
        result = subprocess.run('./%s' % output_bin,
                                input=bytearray(case['i'], 'ascii'),
                                stdout=subprocess.PIPE)
        output = result.stdout.decode('ascii')
        # sometimes there will have a '\n' at end;
        if output != case['o'] and output != case['o'] + '\n':  
            print('=' * 10 + ' Test Case #%s ' % i + '=' * 10)
            print('#input')
            print(case['i'])
            print('#expect')
            print(case['o'])
            print('#output')
            print(output)
            print('=' * 10 + ' Test Failed ' + '=' * 10)
            exit(1)
    print('All Passed, Congratulations!')


def add_test_case(index):
    test_data_path = os.path.join('./data', '%s.yaml' % index.lower())
    if not os.path.exists(test_data_path):
        warnings.warn('no test case in this problem, please check it <%s>' % index)

    with open('./testdata.in') as f:
        i = f.read()

    with open('./testdata.out') as f:
        o = f.read()

    with open(test_data_path) as f:
        test_case = load(f)
        test_case.append({'i': i, 'o': o})

    with open(test_data_path, 'w') as f:
        dump(test_case, f)


def solved_and_commit(index):
    collection = get_collection()
    problem = collection.find_one({'index': index})
    if not problem:
        raise Exception('problem %s not found' % index)

    solution_file = '%s.%s.md' % (index, problem['title'])
    code_file = index.lower() + '.cpp'

    # move files
    to_move = {}
    path_map = {'cpp': 'cpp', 'md': 'solutions'}
    for f in [solution_file, code_file]:
        if not os.path.exists(f):
            warnings.warn('solutions file <%s> not exists' % f)
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

    # update solved tag and  update index table?
    collection.update_one({'index': index}, {'$set': {'solved': True}})
    update_index_table()

    # git commit and push
    git = Repo('../').git
    print(git.add('.'))
    print(git.status())

    default_summary = '%s %s, Solved' % (index, problem['title'])
    commit = input('\nCheck git status, and Input Summary: [%s]\n' % default_summary)
    commit = commit or default_summary
    print(git.commit('-m', commit))

    input('Ready to Push?')
    print(git.push())


from argparse import ArgumentParser

cli = ArgumentParser()
subparsers = cli.add_subparsers(dest="subcommand")


def subcommand(args, exclusive):
    def decorator(func):
        parser = subparsers.add_parser(func.__name__, description=func.__doc__)
        for arg in args:
            parser.add_argument(*arg[0], **arg[1])
        if exclusive:
            group = parser.add_mutually_exclusive_group()
            for arg in exclusive:
                group.add_argument(*arg[0], **arg[1])
        parser.set_defaults(func=func)
    return decorator


def argument(*name_or_flags, **kwargs):
    return ([*name_or_flags], kwargs)


@subcommand([argument('problem', type=str, nargs=1, help='problem id')], [
    argument('-g', '--generate', action='store_true'),
    argument('-t', '--test', action='store_true'),
    argument('-s', '--solve', action='store_true'),
    argument('-a', '--add', action='store_true'),
])
def solve(args):
    print(args.problem)
    if args.generate:
        generate_template(args.problem[0])
    elif args.test:
        compile_and_test(args.problem[0])
    elif args.solve:
        solved_and_commit(args.problem[0])
    elif args.add:
        add_test_case(args.problem[0])


@subcommand([argument('-t', '--table', action='store_true', help='update index table')], [
    argument('-a', '--all', action='store_true'),
    argument('-p', '--page', nargs=1),
    argument('-i', '--index', nargs=1, help='problem id')
])
def update(args):
    if args.all:
        get_all_problems()
    elif args.page:
        update_problems_from_page(args.page[0])
    elif args.index:
        update_problem_detail(args.index[0])

    if args.table:
        update_index_table()


if __name__ == '__main__':
    args = cli.parse_args()
    if args.subcommand is None:
        cli.print_help()
    else:
        args.func(args)