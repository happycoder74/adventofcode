import os
import sys

from importlib.machinery import SourceFileLoader


class AocRunner(object):
    def __init__(self, year=None, day=None, filename=None):
        self.year = year
        self.day = day
        if filename is not None:
            self.filename = filename
        else:
            self.filename = "input.txt"

    def run(self):
        class_list = self.get_classes()
        for year, cls in class_list:
            print(f"Year {year} - {cls.__name__}")
            print("=================================")
            try:
                cls(filename=self.filename).solve_all()
            except ModuleNotFoundError:
                print("Unable to import submodule")
            print("=================================")
            print("")

    def get_classes(self):
        class_list = list()
        if self.day is not None:
            days = [int(self.day)]
        else:
            days = range(1, 26)

        if self.year is not None:
            year = [int(self.year)]
        else:
            year = range(2015, 2023)

        for year in year:
            for day in days:
                module = f"aoc_{year}_{day:02d}"
                sourcefile = os.path.join(f"{year}", f"{day:02d}", f"{module}.py")
                if os.path.exists(sourcefile):
                    try:
                        puzzle = SourceFileLoader(module, sourcefile).load_module()
                        try:
                            cls = getattr(puzzle, f"Day{day}")
                            class_list.append((year, cls))
                        except AttributeError:
                            print(f"No solution for day {day} for {year}")
                    except ModuleNotFoundError:
                        print(f"Unable to import submodule for {year} - {day}")
        self.year = year
        return class_list


if __name__ == "__main__":
    arg_year = None
    arg_day = None
    filename = None
    if len(sys.argv) == 2:
        arg_year = sys.argv[1]
        arg_day = None
    if len(sys.argv) == 3:
        arg_year = sys.argv[1]
        arg_day = sys.argv[2]
    if len(sys.argv) == 4:
        arg_year = sys.argv[1]
        arg_day = sys.argv[2]
        filename = sys.argv[3]

    runner = AocRunner(year=arg_year, day=arg_day, filename=filename)
    runner.run()
