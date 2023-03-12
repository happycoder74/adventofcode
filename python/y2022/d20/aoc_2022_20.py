from collections import deque
from typing import Iterable, List

from common import Puzzle, timer


class Day20(Puzzle, year=2022, day=20):
    @staticmethod
    def clean_input(data: Iterable[str]) -> List[int]:
        return [int(d) for d in data]

    def mix(self, rounds=1) -> int:
        length: int = len(self.data)
        zero = (0, self.data.index(0))
        data = deque(
                [(number, index) for index, number in enumerate(self.data)]
        )
        order = [n for n in self.data]
        for _ in range(rounds):
            for i, number in enumerate(order):
                index = data.index((number, i))
                data.rotate(-index)
                value: tuple[int, int] = data.popleft()
                data.rotate(-value[0])
                data.appendleft(value)

        zero_index = data.index(zero)
        return sum(data[(zero_index + i) % length][0] for i in (1000, 2000, 3000))

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        return self.mix()

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        factor: int = 811589153
        self.data = [n*factor for n in self.data]
        return self.mix(rounds=10)
