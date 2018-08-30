
import os
import time
import warnings
import subprocess

from yaml import load, dump


def compile_and_test(index):

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

    solution_file = regular_file(index, problem['title'])
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
