import itertools

from common import Puzzle, timer


class Day02(Puzzle, year=2017, day=2):
    @staticmethod
    def clean_input(data):
        return [[int(v) for v in l.split()] for l in data]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return sum([max(l) - min(l) for l in self.data])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        checksum = 0
        for line in self.data:
            for num1, num2 in itertools.permutations(line, 2):
                if (num1 % num2) == 0:
                    checksum += num1 // num2
        return checksum
