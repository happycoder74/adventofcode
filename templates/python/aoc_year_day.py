import sys
from common import timer, Puzzle


class Day<DAY>(Puzzle, year=<YEAR>, day=<DAY>):
    @staticmethod
    def clean_input(data):
        return data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return None

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return None


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day<DAY>(filename=filename).solve_all()
