
import os
import time
import warnings

import yaml

from urllib.parse import quote

from scripts.database import db_luogu, get_problem
from scripts.filepath import *
from scripts.spider import extract_test_examples_from_article


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

TEMPLATE_SOLUTION = """
### {index} {title}

{abstract}

#### Description\n\n
#### Analysis\n\n
#### [Code]({code_link})\n\n
"""

TEMPLATE_CPP = """
// {index} {title}
// {problem_link}

"""

TEMPLATE_INDEX_TABLE = """
## {level}

{solved} / {count}

{table}
"""


def make_cpp_template(problem):
    print(problem['problem_link'])
    return TEMPLATE_CPP.format(index=problem['index'],
                               title=problem['title'],
                               problem_link=problem['problem_link'])


def make_solution_template(problem):
    abstract = ''
    algorithm_tags = problem.get('algorithm_tags', [])
    tags = list(filter(lambda t: t not in algorithm_tags, problem.get('tags', {}).values()))
    if algorithm_tags:
        abstract = '算法标签: ' + ', '.join(map(lambda x: '**' + x + '**', algorithm_tags))
    if tags:
        abstract += '\n其他标签: ' + ', '.join(map(lambda x: '**' + x + '**', tags))

    relative_code_link = cpp_relative_path_from_solution(problem['index'])
    return TEMPLATE_SOLUTION.format(index=problem['index'],
                                    title=problem['title'],
                                    abstract=abstract,
                                    code_link=relative_code_link)


def make_problem_item(problem):
    index = problem['index']
    marked = '⭐️' if problem['marked'] else ''
    # avoid '|' in markdown table
    problem_link = '%s[%s](%s)' % (marked, problem['title'].replace('|', '-'), problem['problem_link'])

    algorithm_tags = problem.get('algorithm_tags', [])
    tags = [t for t in problem.get('tags', {}).values() if t not in algorithm_tags]

    solution_link = ''
    code_link = ''
    if problem.get('solved'):
        solution_link = solution_relative_path_from_index_table(index, problem['title'])
        solution_link = '[📜](%s)' % quote(solution_link)
        code_link = cpp_relative_path_from_index_table(index)
        code_link = '[C++](%s)' % quote(code_link)

    return '|'.join(['', index, problem_link, ','.join(algorithm_tags),
                     ','.join(tags), solution_link, code_link, '', ])


def make_index_table(problems):
    headers = ['#', 'Title', 'Algorithm Tags', 'Tags', 'Solution', 'Code']
    markers = [':---:' for _ in headers]
    markers[1] = '---'  # Title
    headers = [''] + headers + ['']
    markers = [''] + markers + ['']

    table = list()
    table.append("|".join(headers))
    table.append("|".join(markers))

    for problem in problems:
        table.append(make_problem_item(problem))

    return '\n'.join(table)


def make_index_table_content(level):
    problems = db_luogu.find({'level': level})
    count = db_luogu.count({'level': level})
    solved = db_luogu.count({'level': level, 'solved': True})
    table = make_index_table(problems)
    return TEMPLATE_INDEX_TABLE.format(level=level, count=count, solved=solved, table=table)


def generate_index_table():
    levels = db_luogu.aggregate([{"$group": {"_id": "$level", "count": {"$sum": 1}}}])
    levels = [l['_id'] for l in levels]

    for l in levels:
        if l not in LEVELS:
            raise Exception('level not match, please check it, %s' % l)

    levels.sort(key=lambda l: LEVELS[l])
    # print(levels)

    for level in levels:
        text = make_index_table_content(level)
        # print(text)
        with open(index_file_path(level), 'w') as f:
            f.write(text)


def generate_cpp_file(problem):
    cpp_file = cpp_file_name(problem['index'])
    cpp_template = make_cpp_template(problem)

    if not os.path.exists(cpp_file):
        with open(cpp_file, 'w') as f:
            f.write(cpp_template)


def generate_solution_file(problem):
    solution_file = solution_file_name(problem['index'], problem['title'])
    if os.path.exists(solution_file):
        warnings.warn('Be careful!!! Overwriting %s' % solution_file)
        time.sleep(1)

    solution_template = make_solution_template(problem)

    with open(solution_file, 'w') as f:
        f.write(solution_template)


def generate_test_data(problem):

    raw_article = problem.get('raw_article')
    if not raw_article:
        print(problem)
        warnings.warn('raw article not found, please check it')

    test_examples = extract_test_examples_from_article(raw_article)

    if not test_examples:
        warnings.warn('test examples not found, please check it')

    print(test_examples)
    # print(yaml.load(yaml.dump(test_examples)))
    test_data_file = test_data_path(problem['index'])

    if not os.path.exists(test_data_file):
        with open(test_data_file, 'w') as f:
            f.write(yaml.dump(test_examples))


def generate_templates(index):
    problem = get_problem(index)
    if not problem:
        raise Exception('problem <%s> not found in db' % index)

    generate_solution_file(problem)
    generate_cpp_file(problem)
    generate_test_data(problem)

