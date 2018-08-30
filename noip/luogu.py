
import fire

from scripts.filepath import fix_file_path, move_tmp_files
from scripts.spider import fetch_raw_problem
from scripts.template import generate_index_table, generate_templates
from scripts.autotest import compile_and_test
from scripts.utils import solved_and_commit


class LuoGuProblem(object):

    def __init__(self, problem):
        self._problem = problem

    def g(self):  # update and generate template
        fetch_raw_problem(self._problem)
        self.start()

    def t(self):  # auto test
        self.autotest()

    def s(self):  # solved and commit
        self.gitcommit()

    def start(self):
        print("generate <{index}> template files".format(index=self._problem))
        generate_templates(self._problem)

    def autotest(self):
        # compile and test
        print("auto test {index}".format(index=self._problem))
        compile_and_test(self._problem)

    def gitcommit(self):
        # move files and git commit
        print("git commit {index}".format(index=self._problem))
        move_tmp_files(self._problem)
        solved_and_commit(self._problem)


class LuoGuFixer(object):
    def structure(self):
        print("fix structure")
        fix_file_path()

    def generate_index(self):
        generate_index_table()


class LuoGuCLI(object):

    def problem(self, index):
        return LuoGuProblem(index)

    def fix(self):
        return LuoGuFixer()


if __name__ == '__main__':
    fire.Fire(LuoGuCLI)