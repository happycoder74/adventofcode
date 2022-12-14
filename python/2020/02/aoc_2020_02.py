import re
import sys
from common import timer, Puzzle


class Day02(Puzzle, year=2020, day=2):
    @staticmethod
    def clean_input(data):
        data = [val.split(' ') for val in data]
        return data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        found = 0
        for p in self.data:
            pattern = fr"{p[1][:-1]}"
            matches = re.findall(pattern, p[2])
            limits = [int(val) for val in p[0].split('-')]
            if (len(matches) >= limits[0]) & (len(matches) <= limits[1]):
                found += 1

        return found

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        found = 0
        for p in self.data:
            pattern = f"{p[1][:-1]}"
            limits = [int(val) - 1 for val in p[0].split('-')]
            if (p[2][limits[0]] == pattern) ^ (p[2][limits[1]] == pattern):
                found += 1

        return found


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day02(filename=filename)
