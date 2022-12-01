import sys
from common import timer, Puzzle


class Day1(Puzzle, year=2022, day=1):
    @staticmethod
    def clean_input(data):
        return data

    def elves(self):
        elves = list()
        cal_sum = 0
        for cals in self.data:
            if cals.strip() == '':
                elves.append(cal_sum)
                cal_sum = 0
            else:
                cal_sum += int(cals)
        return elves

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return max(self.elves())

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        elves_list = self.elves().sort(reverse=True)
        return sum(elves_list[0:3])


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day1(filename=filename).solve_all()
