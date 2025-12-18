import math

from common import Puzzle, timer


class StoneBlinker:
    def __init__(self, stones):
        self.stones = stones
        self.lookup: dict[tuple[int, int], int] = dict()

    def blink(self, stone):
        if stone == 0:
            result = [1]
        else:
            no_digits = math.floor(math.log10(stone)) + 1
            if no_digits % 2 == 0:
                left, right = divmod(stone, (10 ** (no_digits // 2)))
                result = [left, right]
            else:
                result = [stone * 2024]
        self.lookup[(stone, 1)] = len(result)
        return result

    def dp(self, stone: int, times):
        if (stone, times) in self.lookup:
            return self.lookup[(stone, times)]
        else:
            stone_result = self.blink(stone)
            if times > 1:
                self.lookup[(stone, times)] = sum(self.dp(s, times - 1) for s in stone_result)
            return self.lookup[(stone, times)]

    def solve(self, iterations=1):
        return sum(self.dp(stone, iterations) for stone in self.stones)


class Day11(Puzzle, year=2024, day=11):
    @staticmethod
    def clean_input(data) -> list[int]:
        return [int(v) for v in data[0].strip().split()]

    @timer(part=1)
    def solve_part_1(self) -> int:
        return StoneBlinker(self.data).solve(25)

    @timer(part=2)
    def solve_part_2(self):
        return StoneBlinker(self.data).solve(75)
