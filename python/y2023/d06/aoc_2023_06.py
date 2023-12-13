import math
from common import timer, Puzzle


class Day06(Puzzle, year=2023, day=6):
    @staticmethod
    def clean_input(data):
        times = list(map(int, data[0].split()[1:]))
        dist = list(map(int, data[1].split()[1:]))
        data = {time: distance for time, distance in zip(times, dist)}
        return data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        prod = 1
        a = -1
        self.f = lambda a, b, c: (
            (-b + math.sqrt(b**2 - 4 * a * c)) / (2 * a),
            (-b - math.sqrt(b**2 - 4 * a * c)) / (2 * a),
        )

        for time, distance in self.data.items():
            x1, x2 = self.f(a, time, -distance)
            prod *= math.ceil(x2) - math.floor(x1) - 1
        return prod

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        time = int("".join([f"{t}" for t in self.data.keys()]))
        distance = int("".join([f"{d}" for d in self.data.values()]))
        a = -1
        x1, x2 = self.f(a, time, -distance)

        return math.ceil(x2) - math.floor(x1) - 1
