import sys

from common import Parser, Puzzle, timer


def aggfunc(x):
    w, l, h = x
    xx, yy = sorted(x)[:2]
    return 2 * w * l + 2 * l * h + 2 * h * w + xx * yy


def ribbon(x):
    w, l, h = x
    xx, yy = sorted(x)[:2]
    return 2 * xx + 2 * yy + w * l * h


class Day02(Puzzle, year=2015, day=2):
    @staticmethod
    def clean_input(data):
        return [[int(v) for v in x.split("x")] for x in data]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return sum(map(aggfunc, self.data))

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return sum(map(ribbon, self.data))
