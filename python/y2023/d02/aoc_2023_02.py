import re
from common import timer, Puzzle


class Day02(Puzzle, year=2023, day=2):
    @staticmethod
    def clean_input(data):
        return data

    def max_color(self, item: str, color: str) -> int:
        pattern = r"\d+(?=\s" + color + ")"
        return max([int(s) for s in re.findall(pattern, item)])

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        valid = 0
        for i, item in enumerate(self.data):
            if (
                (self.max_color(item, "red") <= 12)
                and (self.max_color(item, "green") <= 13)
                and (self.max_color(item, "blue") <= 14)
            ):
                valid += i + 1

        return valid

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        result = 0
        for item in self.data:
            result += (
                self.max_color(item, "red")
                * self.max_color(item, "green")
                * self.max_color(item, "blue")
            )
        return result
