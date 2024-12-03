import re

from common import Puzzle, timer


class Day03(Puzzle, year=2024, day=3):
    @staticmethod
    def clean_input(data) -> list[str]:
        return data

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        result = 0
        for line in self.data:
            numbers = re.findall(r"mul\((\d+),(\d+)\)", line)
            result += sum([int(v[0]) * int(v[1]) for v in numbers])
        return result

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        result = 0
        enabled = True
        for line in self.data:
            instructions = re.findall(r"(mul\((\d+),(\d+)\)|don\'t\(\)|do\(\))", line)
            for inst in instructions:
                if inst[0] == "don't()":
                    enabled = False
                elif inst[0] == "do()":
                    enabled = True
                else:
                    if enabled:
                        result += int(inst[1]) * int(inst[2])

        return result
