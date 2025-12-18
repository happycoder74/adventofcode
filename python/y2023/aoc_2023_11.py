import itertools

from common import Helpers, Puzzle, timer


class Day11(Puzzle, year=2023, day=11):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)

    @staticmethod
    def clean_input(data):
        return data

    def solver(self, multiplier: int = 2) -> int:
        sum_distance: int = 0

        galaxies = [
            (r, c) for r, row in enumerate(self.data) for c, col in enumerate(row) if col == "#"
        ]
        blank_rows = set(range(0, len(self.data))).difference(set([g[0] for g in galaxies]))
        blank_cols = set(range(0, len(self.data[0]))).difference(set([g[1] for g in galaxies]))

        for g1, g2 in itertools.combinations(galaxies, 2):
            d = abs(g1[0] - g2[0]) + abs(g1[1] - g2[1])
            min_r, max_r = Helpers.minmax(g1[0], g2[0])
            min_c, max_c = Helpers.minmax(g1[1], g2[1])
            extras = 0
            for row in blank_rows:
                if min_r <= row <= max_r:
                    extras += 1
            for row in blank_cols:
                if min_c <= row <= max_c:
                    extras += 1
            sum_distance += d + extras * (multiplier - 1)
        return sum_distance

    @timer(part=1)
    def solve_part_1(self):
        return self.solver()

    @timer(part=2)
    def solve_part_2(self):
        if self.filename == "test_input.txt":
            multiplier = 10
        else:
            multiplier = 1_000_000

        return self.solver(multiplier)
