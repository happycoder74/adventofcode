from common import timer, Puzzle
from collections import Counter


class Day06(Puzzle, year=2022, day=6):
    @staticmethod
    def clean_input(data):
        return data[0]

    @staticmethod
    def marker(data, markerlength):
        for i in range(0, len(data) - markerlength):
            if len(Counter(data[i:i+markerlength])) == markerlength:
                return i+markerlength
        return None

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.marker(self.data, 4)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.marker(self.data, 14)
