import os
import sys
from pathlib import Path

from common import timer


class Puzzle(object):
    def __init_subclass__(cls, year=None, day=None, stripped=True, **kwargs):
        super().__init_subclass__(**kwargs)
        cls.year = year
        cls.day = day

    def __init__(self, year=None, day=None, filename=None, data=None, stripped=True):
        self.filename = filename
        if year is not None:
            self.year = year
        if day is not None:
            self.day = day
        if data is None:
            data = self.get_input(stripped=stripped)
        self.data = self.clean_input(data)

    def get_input(self, mode=None, stripped=True):
        if envpath := os.getenv("AOC_DATA_LOCATION"):
            filename = Path(envpath) / Path(f"{self.year}") / Path(f"{self.day:02d}")
        else:
            filename = (
                Path(__file__).parent.parent.parent
                / Path("data")
                / Path(f"{self.year}")
                / Path(f"{self.day:02d}")
            )
        if self.filename is None:
            fn = "input.txt"
            filename = filename / Path(fn)
        elif self.filename == "test_input.txt":
            fn = self.filename
            filename = filename / Path(fn)
        else:
            filename = self.filename
        try:
            with open(filename) as fp:
                if stripped:
                    data = fp.read().strip().splitlines()
                else:
                    data = fp.read().splitlines()
        except FileNotFoundError:
            print("Can not open file {}".format(filename))
            sys.exit(-1)

        return data

    @staticmethod
    def clean_input(data):
        return data

    @staticmethod
    def parse_input_groups(data):
        groups = list()
        group = list()
        for row in data:
            if row == "":
                groups.append(group)
                group = list()
            else:
                group.append(row)
        if len(group) > 0:
            groups.append(group)

        return groups

    @staticmethod
    def parse_int_input(data):
        return [int(d) for d in data]

    @timer(part="main", title="Total elapsed", show_return=False)
    def solve_all(self):
        part1 = self.solve_part_1()
        part2 = self.solve_part_2()
        return part1, part2

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return None

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return None
