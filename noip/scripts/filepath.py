

import os
import shutil


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


def regular_file(*segments, join='.', suffix='.md'):
    segments = map(lambda s: s.replace('/', '-'), segments)
    return join.join(segments) + suffix


def index_file_name(level):
    return str(LEVELS[level]) + '.' + level.replace('/', '.') + '.md'


def index_file_path(level):
    return os.path.join('index', index_file_name(level))


def cpp_file_name(index):
    return index.lower() + '.cpp'


def subdir(index):
    if index[0] == 'P' or index[0] == 'p':  # luogu normal problem starts with P
        sub_index = int(index[1:5]) // 100    # max 100 files per sub dir
        return str(sub_index)
    else:
        return 'others'  # TODO


def test_data_dir(index):
    return os.path.join('data', subdir(index))


def test_data_path(index):
    return os.path.join('data', subdir(index), index.lower() + '.yaml')


def cpp_save_dir(index):
    return os.path.join('cpp', subdir(index))


def cpp_save_path(index):
    return os.path.join('cpp', subdir(index), cpp_file_name(index))


def solution_file_name(index, raw_name):
    return regular_file(index, raw_name, suffix='.md')


def solution_save_dir(index):
    return os.path.join('solutions', subdir(index))


def solution_save_path(index, raw_name):
    return os.path.join('solutions', subdir(index), solution_file_name(index, raw_name))


def relative_path(absolute_path, depth=0):
    return os.path.join('../' * depth, absolute_path)


def cpp_relative_path_from_solution(index):
    return relative_path(cpp_save_path(index), 2)


def cpp_relative_path_from_index_table(index):
    return relative_path(cpp_save_path(index), 1)


def solution_relative_path_from_index_table(index, raw_name):
    return relative_path(solution_save_path(index, raw_name), 1)


def list_files(path):
    all_path = [os.path.join(path, f) for f in os.listdir(path)]
    # print(all_path)
    return list(filter(lambda f: os.path.isfile(f), all_path))


def move_tmp_files(index):
    # move tmp files to save path
    all_files = os.listdir('.')
    tmp_files = filter(lambda x: x.lower().startswith(index.lower()), all_files)
    # print(list(tmp_files))


    move_to = {}
    for f in tmp_files:
        if f.endswith('.md'):
            move_to[f] = solution_save_path(index.upper(), f[len(index) + 1:-3])
        elif f.endswith('.cpp'):
            move_to[f] = cpp_save_path(index)

    if move_to:
        print('Plan to Move:\n')
        for src, dst in move_to.items():
            print('\t %s ---> %s' % (src, dst))
        input('\nReady to Move?')

        for src, dst in move_to.items():
            shutil.move(src, dst)


def fix_file_path():
    base_dir = './solutions'
    files = list_files(base_dir)

    print(files)

    for old_path in files:
        index = int(os.path.basename(old_path)[1:5])
        # index = os.path.basename(f).split('.')[0].upper()
        subdir_path = os.path.join(base_dir, str(index // 100))
        if not os.path.exists(subdir_path):
            os.mkdir(subdir_path)

        new_path = os.path.join(subdir_path, os.path.basename(old_path))
        print(index, old_path, new_path)
        shutil.move(old_path, new_path)


# def fix_solution_file_name():
#     base_dir = './solutions'
#     all_files = list_files(base_dir)
#
#     for f in all_files:
#         old_path = f
#         base_name = os.path.basename(f)
#         new_path = regular_file(*base_name.split('.'), )

