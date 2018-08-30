

import os
import shutil


def regular_file(*segments, join='.', suffix='.md'):
    segments = map(lambda s: s.replace('/', '-'), segments)
    return join.join(segments) + suffix


def cpp_file_name(index):
    return index.lower() + '.cpp'


def subdir(index):
    if index[0] == 'P':  # luogu normal problem starts with P
        sub_index = int(index[1:5]) // 100 * 100    # max 100 files per sub dir
        return str(sub_index) + '-' + str(sub_index + 99)
    else:
        return 'others'  # TODO


def cpp_save_path(index):
    return os.path.join('cpp', subdir(index), cpp_file_name(index))


def solution_file_name(index, raw_name):
    return regular_file(index, raw_name, suffix='.md')


def solution_save_path(index, raw_name):
    return os.path.join('solution', subdir(index), solution_file_name(index, raw_name))


def relative_path(absolute_path, depth=0):
    return os.path.join('../' * depth, absolute_path)


def cpp_relative_path_from_solution(index):
    return relative_path(cpp_save_path(index), 2)


def cpp_relative_path_from_index_table(index):
    return relative_path(cpp_save_path(index), 1)


def solution_relative_path_from_index_table(index, raw_name):
    return relative_path(solution_save_path(index, raw_name), 1)


def fix_file_path():
    cpp_dir = './cpp'
    cpp_files = [os.path.join(cpp_dir, fn) for fn in os.listdir(cpp_dir)]
    cpp_files = filter(lambda f: os.path.isfile(f), cpp_files)

    for f in cpp_files:
        index = os.path.basename(f).split('.')[0].upper()
        subdir_path = os.path.join(os.path.dirname(f), subdir(index))
        if not os.path.exists(subdir_path):
            os.mkdir(subdir_path)


