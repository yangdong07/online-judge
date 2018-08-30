
import os

from urllib.parse import quote

from scripts.database import *
from scripts.filepath import *


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

#include <cstdio>

int main()
{
    return 0;
}
"""

TEMPLATE_INDEX_TABLE = """
## {level}

{solved} / {count}

{table}
"""


def make_cpp_template(problem):
    return TEMPLATE_CPP.format(index=problem['index'],
                                     title=problem['title'],
                                     problem_link=problem['problem_link'])


def make_solution_template(problem):
    abstract = ''
    algorithm_tags = problem.get('algorithm_tags', [])
    tags = list(filter(lambda t: t not in algorithm_tags, problem.get('tags', {}).values()))
    if algorithm_tags:
        abstract = '算法标签: ' + ', '.join(map(lambda x: '**' + x + '**', algorithm_tags)) + '\n'
    if tags:
        abstract += '其他标签: ' + ', '.join(map(lambda x: '**' + x + '**', tags)) + '\n'

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

    return '|'.join([
        '',
        index,
        problem_link,
        ','.join(algorithm_tags),
        ','.join(tags),
        solution_link,
        code_link,
        '',
    ])


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


def update_index_table():
    levels = db_luogu.aggregate([{"$group": {"_id": "$level", "count": {"$sum": 1}}}])
    levels = [l['_id'] for l in levels]

    for l in levels:
        if l not in LEVELS:
            raise Exception('level not match, please check it, %s' % l)

    levels.sort(key=lambda l: LEVELS[l])

    print(levels)

    for level in levels:
        text = make_index_table_content(level)
        # print(text)
        with open(index_file_path(level), 'w') as f:
            f.write(text)