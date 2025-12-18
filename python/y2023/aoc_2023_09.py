import functools

from common import Puzzle, timer


class Day09(Puzzle, year=2023, day=9):
    @staticmethod
    def clean_input(data):
        return [[int(v) for v in row.split()] for row in data]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        values = []
        for row in self.data:
            r = row
            row_values = []
            while any(r):
                row_values.append(r[-1])
                r = [y - x for x, y in zip(r[:-1], r[1:])]
            values.append(sum(row_values))
        return sum(values)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        values = []
        for row in self.data:
            r = row
            row_values = []
            while any(r):
                row_values.append(r[0])
                r = [y - x for x, y in zip(r[:-1], r[1:])]
            values.append(functools.reduce(lambda a, b: b - a, reversed(row_values)))

        return sum(values)
