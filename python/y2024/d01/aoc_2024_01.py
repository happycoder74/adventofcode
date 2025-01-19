from collections import Counter

from common import Puzzle, timer


class Day01(Puzzle, year=2024, day=1):
    @staticmethod
    def clean_input(data):
        left = []
        right = []
        for row in data:
            items = row.split(" ")
            left.append(int(items[0]))
            right.append(int(items[-1]))

        return left, right

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return sum(
            [abs(a - b) for a, b in zip(sorted(self.data[0]), sorted(self.data[1]))]
        )

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        lefts = Counter(self.data[0])
        rights = Counter(self.data[1])
        s = 0
        for key, val in lefts.items():
            s += val * (rights[key] * key)

        return s
