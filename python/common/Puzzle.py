import os
from common import timer


class Puzzle(object):
    def __init__(self, filename, year, day):
        print(f"Reading {filename} from {year}/{day}")
        self.filename = filename
        self.year = year
        self.day = day
        self.data = self.clean_input(self.get_input())

    def get_input(self, mode=None):
        path = os.path.join(os.path.dirname(__file__),
                            f"../../data/{self.year}/{self.day:02d}")
        with open(os.path.join(path, self.filename)) as fp:
            data = fp.read().strip().splitlines()

        return self.clean_input(data)

    def clean_input(self, data):
        return data

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
