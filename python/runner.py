#!/usr/bin/env python3
import argparse
import os

from common import timer

from importlib.machinery import SourceFileLoader


class AocRunner(object):
    def __init__(self, year=None, day=None, filename=None, data=None):
        self.year = year
        self.day = day
        self.data = None
        self.filename = None
        if filename is not None:
            self.filename = filename
        else:
            if data is None:
                self.filename = "input.txt"
            else:
                self.data = data
                print(f"{self.data=}")

    @timer(part=0, title="Total run time", show_return=False)
    def run(self):
        class_list = self.get_classes()
        for year, cls in class_list:
            print(f"Year {year} - {cls.__name__}")
            print("=================================")
            try:
                cls(filename=self.filename, data=self.data).solve_all()
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
                sourcefile = os.path.join(
                    f"{year}", f"{day:02d}", f"{module}.py"
                )
                if os.path.exists(sourcefile):
                    try:
                        puzzle = SourceFileLoader(
                            module, sourcefile
                        ).load_module()
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
    parser = argparse.ArgumentParser(
        prog="runner.py", description="Run Advent of Code solutions"
    )
    parser.add_argument("filename", nargs="?", help="Filename to be used")
    parser.add_argument("--test", help="Run test case", action="store_true")
    parser.add_argument("-y", "--year", help="Year to be run")
    parser.add_argument("-d", "--day", help="Year to be run")
    parser.add_argument("--data", help="Direct input of data")

    args = parser.parse_args()
    data = args.data.split(",") if args.data else None

    runner = AocRunner(year=args.year,
                       day=args.day,
                       filename=args.filename,
                       data=data)
    runner.run()
