
import os

from .filepath import cpp_relative_path_from_solution


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

luogu_template_md = """
### {index} {title}

{abstract}

#### Description\n\n
#### Analysis\n\n
#### [Code]({code_link})\n\n
"""

luogu_template_cpp = """
// {index} {title}
// {problem_link}

#include <cstdio>

int main()
{
    return 0;
}
"""



def make_cpp_template(problem):
    return luogu_template_cpp.format(index=problem['index'],
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
    return luogu_template_md.format(index=problem['index'],
                                    title=problem['title'],
                                    abstract=abstract,
                                    code_link=relative_code_link)


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


def make_