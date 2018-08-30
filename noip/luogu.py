
import fire

from scripts.filepath import fix_file_path
from scripts.template import update_index_table


class LuoGuProblem(object):

    def __init__(self, problem):
        self._problem = problem

    def g(self):  # generate template
        self.start()

    def t(self):  # auto test
        self.autotest()

    def s(self):  # solved and commit
        self.gitcommit()

    def start(self):
        print("start {index}".format(index=self._problem))

    def autotest(self):
        # compile and test
        print("auto test {index}".format(index=self._problem))

    def gitcommit(self):
        # compile and test
        print("auto test {index}".format(index=self._problem))


class LuoGuFixer(object):
    def structure(self):
        print("fix structure")
        fix_file_path()

    def update_index(self):
        update_index_table()


class LuoGuCLI(object):

    def problem(self, index):
        return LuoGuProblem(index)

    def fix(self):
        return LuoGuFixer()


if __name__ == '__main__':
    fire.Fire(LuoGuCLI)