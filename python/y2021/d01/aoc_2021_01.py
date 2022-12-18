from common import timer, Puzzle


class Day01(Puzzle, year=2021, day=1):
    @staticmethod
    def clean_input(data):
        return [int(d) for d in data]

    def solution(self, window):
        return len(
            [(a, b) for a, b in zip(self.data, self.data[window:]) if b > a]
        )

    @timer(part=1)
    def solve_part_1(self):
        """ Solution for part 1 """
        return self.solution(window=1)

    @timer(part=2)
    def solve_part_2(self):
        """ Solution for part 2 """
        return self.solution(window=3)
