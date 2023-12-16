from common import Puzzle, timer


class Day09(Puzzle, year=2023, day=9):
    @staticmethod
    def clean_input(data):
        return [[int(v) for v in row.split()] for row in data]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        values = []
        r = dict()
        for row in self.data:
            r[0] = row
            level = 0
            while any(r[level]):
                level += 1
                r[level] = [y - x for x, y in zip(r[level - 1][:-1], r[level - 1][1:])]
            while level > 0:
                r[level - 1].append(r[level - 1][-1] + r[level][-1])
                level -= 1
            values.append(r[0][-1])

        return sum(values)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        values = []
        r = dict()
        for row in self.data:
            r[0] = row
            level = 0
            while any(r[level]):
                level += 1
                r[level] = [y - x for x, y in zip(r[level - 1][:-1], r[level - 1][1:])]
            while level > 0:
                r[level - 1].insert(0, r[level - 1][0] - r[level][0])
                level -= 1
            values.append(r[0][0])

        return sum(values)
