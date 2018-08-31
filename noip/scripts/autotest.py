
import os
import time
import warnings
import subprocess

from yaml import load, dump

from scripts.filepath import cpp_file_name, test_data_path


output_bin = 'test.out'

TEST_OUTPUT_TEMPLATE = """
=========== Test Case {_id} ===========
# input
{_input}
# expect
{_expect}
# ouptut
{_output}
# error
{_error}
# time used = {time_used}
=========== Test {status} =============
"""


def compress_text(text):
    if len(text) < 200:
        return text
    return '\n'.join([text[:100], '...', text[-100:]])


def gcc_compile(cpp_file):
    result = subprocess.run('g++ {src} -o {o}'.format(src=cpp_file, o=output_bin), shell=True)
    if result.returncode != 0:
        exit(result.returncode)


def load_test_data(index):
    test_file = test_data_path(index)
    if not os.path.exists(test_file):
        raise Exception('no test case in this problem, please check it <%s>' % index)

    with open(test_file, 'r') as f:
        test_case = load(f)

    return test_case


def test(data):
    start_time = time.time()
    result = subprocess.run('./%s' % output_bin,
                            input=bytearray(data, 'ascii'),
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE)
    output = result.stdout.decode('ascii').strip()
    error = result.stderr.decode('ascii')
    return output, error, time.time() - start_time


def compile_and_test(index, _id=None):
    cpp_file = cpp_file_name(index)

    gcc_compile(cpp_file)

    test_data = load_test_data(index)

    all_passed = True
    for i, data in enumerate(test_data, 1):
        output, error, time_used = test(data['i'])
        status = 'Failed' if output.strip() != data['o'].strip() else 'Success'
        if status == 'Failed':
            all_passed = False
        print(TEST_OUTPUT_TEMPLATE.format(_id=i, _input=compress_text(data['i']),
                                          _expect=data['o'],
                                          _output=output, status=status,
                                          _error=error, time_used=time_used))
    if all_passed:
        print('All Passed, Congratulations!')


def add_test_example(index):
    test_data_file = test_data_path(index)

    with open('./testdata.in') as f:
        i = f.read()

    with open('./testdata.out') as f:
        o = f.read()

    test_examples = [{'i': i, 'o': o}]

    if os.path.exists(test_data_file):
        with open(test_data_file) as f:
            test_examples.extend(load(f))
    print(test_examples)

    with open(test_data_file, 'w') as f:
        dump(test_examples, f)


