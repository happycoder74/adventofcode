import itertools
import sys
from common import timer, Puzzle
from SnailFishNumber import SnailfishNumber


class Day18(Puzzle, year=2021, day=18):
    def clean_input(self, data):
        return [line.replace(" ", "") for line in data]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        number = SnailfishNumber(self.data[0])
        for num in self.data[1:]:
            number = number + SnailfishNumber(num)

        return SnailfishNumber.magnitude(number)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        magnitudes = []
        numbers = self.data
        for i, j in itertools.permutations(range(len(self.data)), 2):
            magnitudes.append(SnailfishNumber.magnitude(
                    SnailfishNumber(numbers[i]) + SnailfishNumber(numbers[j])
                )
            )
        return max(magnitudes)


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day18(filename=filename).solve_all()
