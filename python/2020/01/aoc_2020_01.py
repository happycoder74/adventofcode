import numpy as np
import sys
from common import timer, Puzzle


class Day01(Puzzle, year=2020, day=1):
    @staticmethod
    def clean_input(data):
        data = [int(num.strip()) for num in data]
        return np.array(data)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        for num in self.data:
            rest = self.data[self.data >= (2020 - num)]
            for n in rest:
                if n + num == 2020:
                    return n * num
        return None

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        for num1 in self.data:
            for num2 in self.data[self.data > num1]:
                rest = self.data[self.data >= (2020 - num1 - num2)]
                for n in rest:
                    if n + num1 + num2 == 2020:
                        return n * num1 * num2
        return None


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day01(filename=filename)
