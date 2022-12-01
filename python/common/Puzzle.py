import os
from common import timer


class Puzzle(object):
    def __init_subclass__(cls, year=None, day=None, **kwargs):
        super().__init_subclass__(**kwargs)
        cls.year = year
        cls.day = day

    def __init__(self, year=None, day=None, filename=None):
        self.filename = filename
        if year is not None:
            self.year = year
        if day is not None:
            self.day = day
        self.data = self.clean_input(self.get_input())

    def get_input(self, mode=None):
        path = os.path.join(os.path.dirname(__file__),
                            f"../../data/{self.year}/{self.day:02d}")
        with open(os.path.join(path, self.filename)) as fp:
            data = fp.read().strip().splitlines()

        return data

    @staticmethod
    def clean_input(data):
        return data

    @staticmethod
    def parse_input_groups(data):
        groups = list()
        group = list()
        for row in data:
            if row == '':
                groups.append(group)
                group = list()
            else:
                group.append(row)
        if len(group) > 0:
            groups.append(group)

        return groups

    @timer(part='main', title='Total elapsed', show_return=False)
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
