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

code1 = next(lines)
c1 = 1
for c in code1:
    c1 *= (ord(c) - ord('A') + 1)

c2 = 1
code2 = next(lines)
for c in code2:
    c2 *= (ord(c) - ord('A') + 1)

if c1 % 47 == c2 % 47:
    write_result("GO")
else:
    write_result("STAY")
