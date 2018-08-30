

from git import Repo

from scripts.database import db_luogu, get_problem
from scripts.filepath import move_tmp_files
from scripts.template import generate_index_table


def solved_and_commit(index):
    # change status
    db_luogu.update_one({'index': index}, {'$set': {'solved': True}})
    generate_index_table()

    # git commit and push
    git = Repo('../').git
    print(git.add('.'))
    print(git.status())

    problem = get_problem(index)
    default_summary = '%s %s, Solved' % (index, problem['title'])
    commit = input('\nCheck git status, and Input Summary: [%s]\n' % default_summary)
    commit = commit or default_summary
    print(git.commit('-m', commit))

    input('Ready to Push?')
    print(git.push())