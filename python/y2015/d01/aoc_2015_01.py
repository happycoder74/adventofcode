import sys
from common import timer, Puzzle


class Day1(Puzzle, year=2015, day=1):
    @staticmethod
    def clean_input(data):
        return data[0]

    @timer(part=1)
    def solve_part_1(self):
        """ Solution for part 1 """
        return self.data.count("(") - self.data.count(")")

    @timer(part=2)
    def solve_part_2(self):
        """ Solution for part 2 """
        for i, c in enumerate(self.data):
            if self.data[:i + 1].count("(") < self.data[:i + 1].count(")"):
                return i + 1
        return None


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day1(filename=filename).solve_all()
