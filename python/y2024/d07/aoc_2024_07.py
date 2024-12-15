import itertools
import math
import operator

from common import Puzzle, timer


class Day07(Puzzle, year=2024, day=7):

    @staticmethod
    def clean_input(data) -> list[tuple[int, list[int]]]:
        equations = [
            (int(d.split(": ")[0]), [int(val) for val in d.split(": ")[1].split()]) for d in data
        ]

        return equations

    def check_equation(self, equation, concatenate=False) -> bool:
        answer = equation[0]
        operands = equation[1]
        if concatenate:
            operatorlist = [operator.add, operator.mul, self.concatenate]
        else:
            operatorlist = [operator.add, operator.mul]

        operators = itertools.product(operatorlist, repeat=len(operands) - 1)
        res = 0
        for oplist in operators:
            res = operands[0]
            for i, op in enumerate(oplist):
                res = op(res, operands[i + 1])
                if res > answer:
                    break
            if res == answer:
                return True
        return False

    def concatenate(self, a, b):
        return a * 10 ** int(math.log10(b) + 1) + b

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        return sum([equation[0] for equation in self.data if self.check_equation(equation)])

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        result = 0
        for equation in self.data:
            if self.check_equation(equation) or self.check_equation(equation, concatenate=True):
                result += equation[0]
        return result
