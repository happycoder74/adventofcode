from common import timer, Puzzle


class Day01(Puzzle, year=2017, day=1):
    @staticmethod
    def clean_input(data):
        return data[0]

    def solution(self, data, step=1):
        return sum(
            [
                int(c1)
                for c1, c2 in zip(data, f"{data[step:]}{data[:step]}")
                if c1 == c2
            ]
        )

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.solution(self.data, step=1)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.solution(self.data, len(self.data) // 2)
