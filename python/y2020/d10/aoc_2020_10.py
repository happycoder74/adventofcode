from collections import defaultdict
from functools import reduce
from operator import mul

from common import Puzzle, timer


def fn(n):
    match (n):
        case 4:
            return 7
        case 3:
            return 4
        case 2:
            return 2
        case _:
            return 1


class Day10(Puzzle, year=2020, day=10):
    @staticmethod
    def clean_input(data):
        return_data = sorted([int(v) for v in data])
        return_data.insert(0, 0)
        return_data.append(return_data[-1] + 3)
        return return_data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        diffs = [v2 - v1 for v1, v2 in zip(self.data[:-1], self.data[1:])]
        count = defaultdict(int)
        for d in diffs:
            count[d] += 1

        return (count[1]) * (count[3])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        diffs = [v2 - v1 for v1, v2 in zip(self.data[:-1], self.data[1:])]
        diffs.insert(0, 3)
        indices = [i for i, v in enumerate(diffs) if v == 3]
        n = [v2 - v1 - 1 for v1, v2 in zip(indices[:-1], indices[1:])]
        return reduce(mul, map(fn, n), 1)
