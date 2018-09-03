
import os
import fire


TEMPLATE_HEAD = """/*
ID: yesimim1
TASK: {task}
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("{task}.in", "r");
    FILE *fout = fopen ("{task}.out", "w");

#include <fstream>
    ofstream fout ("{task}.out");
    ifstream fin ("{task}.in");
*/"""

def replace_io(s):
    return s.replace("cin", "fin") \
            .replace("cout", "fout") \
            .replace("getchar()", "fgetc(fin)") \
            .replace("scanf(", "fscanf(fin, ") \
            .replace("printf(", "fprintf(fout, ")


def replace_task(s, task):
    _in = task + '.in'
    _out = task + '.out'
    return s.replace(_in, 'test.in').replace(_out, 'test.out')


def make_copy_for_test(task):
    lines = []
    with open(task + '.cpp', 'r') as f:
        for line in f:
            lines.append(replace_task(line, task))

    with open('tmp.cpp', 'w') as f:
        f.writelines(lines)


class USACO(object):
    def copy(self, src, task):
        with open(src, 'r') as origin, open(task + '.cpp', 'w') as f:
            f.write(TEMPLATE_HEAD.format(task=task))
            line = ''
            for line in origin:
                if line.startswith('#'):  # skip lines
                    break
            f.write('\n\n')
            f.write(line)
            for line in origin:
                f.write(replace_io(line))

    def test(self, task):
        make_copy_for_test(task)


if __name__ == '__main__':
    fire.Fire(USACO)