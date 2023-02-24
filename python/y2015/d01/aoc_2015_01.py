from common import timer, Puzzle


class Day01(Puzzle, year=2015, day=1):
    @staticmethod
    def clean_input(data) -> str:
        return data[0]

    @timer(part=1)
    def solve_part_1(self) -> int:
        """ Solution for part 1 """
        return self.data.count("(") - self.data.count(")")

    @timer(part=2)
    def solve_part_2(self) -> int:
        """ Solution for part 2 """
        for i, _ in enumerate(self.data):
            if self.data[:i + 1].count("(") < self.data[:i + 1].count(")"):
                return i + 1
        return 0
