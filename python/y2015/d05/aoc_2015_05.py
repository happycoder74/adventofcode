import re
from common import timer, Puzzle


class Day05(Puzzle, year=2015, day=5):
    @staticmethod
    def clean_input(data) -> bool:
        return data

    @staticmethod
    def check_wovels(line) -> bool:
        return len(re.findall(r"[aeiou]", line)) >= 3

    @staticmethod
    def check_dbl_letter(line) -> bool:
        return len(re.findall(r"(.)\1", line)) > 0

    @staticmethod
    def check_invalid(line) -> bool:
        pattern = r"(ab|cd|pq|xy)"
        return len(re.findall(pattern, line)) == 0

    @staticmethod
    def check_pairs(line) -> bool:
        pattern = r"([a-z][a-z])\w*\1"
        return len(re.findall(pattern, line)) > 0

    @staticmethod
    def check_repeat(line) -> bool:
        pattern = r"(.)\w\1"
        return len(re.findall(pattern, line)) > 0

    @staticmethod
    def is_nice(line) -> bool:
        return (Day05.check_wovels(line)
                and Day05.check_dbl_letter(line)
                and Day05.check_invalid(line))

    @staticmethod
    def is_nice_2(line) -> bool:
        return (Day05.check_pairs(line) and Day05.check_repeat(line))

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        return len([1 for line in self.data if Day05.is_nice(line)])

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        return len([1 for line in self.data if Day05.is_nice_2(line)])
