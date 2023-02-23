import numpy as np
from common import timer, Puzzle


class Day07(Puzzle, year=2021, day=7):
    @staticmethod
    def clean_input(data):
        return np.array([int(num) for num in data[0].split(',')])

    @staticmethod
    def calc_fuel(data, pos, part):
        if part == 1:
            return sum(abs(data - pos))
        else:
            return sum([sum(range(abs(d - pos) + 1)) for d in data])

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        min_pos = min(self.data)
        min_fuel = Day07.calc_fuel(self.data, min_pos, part=1)

        for pos in self.data:
            fuel = Day07.calc_fuel(self.data, pos, part=1)
            if fuel < min_fuel:
                min_fuel = fuel
                min_pos = pos
        return min_fuel

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        min_pos = min(self.data)
        min_fuel = Day07.calc_fuel(self.data, min_pos, part=2)

        for pos in range(0, max(self.data)+1):
            fuel = Day07.calc_fuel(self.data, pos, part=2)
            if fuel < min_fuel:
                min_fuel = fuel
                min_pos = pos
        return min_fuel
