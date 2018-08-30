"""
ID: yesimim1
LANG: PYTHON3
TASK: ride
"""
TASK_NAME = 'ride'  # test


def write_result(result):
    with open(TASK_NAME + '.out', 'w') as f:
        f.write(str(result) + '\n')


def read_lines():
    with open(TASK_NAME + '.in', 'r') as f:
        for line in f:
            yield line.strip()

lines = read_lines()
