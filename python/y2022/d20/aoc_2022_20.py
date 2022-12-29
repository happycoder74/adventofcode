from collections import deque
from common import timer, Puzzle


class Day20(Puzzle, year=2022, day=20):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)

    @staticmethod
    def clean_input(data):
        return [int(d) for d in data]

    def mix(self, rounds=1):
        length = len(self.data)
        zero = (0, self.data.index(0))
        data = deque(
            [(number, index) for index, number in enumerate(self.data)]
        )
        order = [n for n in self.data]
        for _ in range(rounds):
            for i, number in enumerate(order):
                index = data.index((number, i))
                data.rotate(-index)
                value = data.popleft()
                data.rotate(-value[0])
                data.appendleft(value)

        zero_index = data.index(zero)
        return sum(data[(zero_index + i) % length][0] for i in (1000, 2000, 3000))

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.mix()

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        factor = 811589153
        self.data = [n*factor for n in self.data]
        return self.mix(rounds=10)
