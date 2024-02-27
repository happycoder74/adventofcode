import itertools

from common import Helpers, Puzzle, timer


class Spiral:
    def __init__(self, pos=(0, 0)):
        self.pos = pos
        self.grid = {self.pos: 1}
        self.deltas = self.get_deltas()

    def get_deltas(self):
        return set(itertools.product((-1, 0, 1), (-1, 0, 1))).difference(set({(0, 0)}))

    def next_step(self):
        x, y = self.pos

        if (x > 0) and (abs(x) > abs(y)):
            y += 1
        elif (x < 0) and ((abs(x) > abs(y)) or (x == -y)):
            y -= 1
        elif (y > 0) and ((abs(y) > abs(x)) or (x == y)):
            x -= 1
        else:
            x += 1

        self.grid[(x, y)] = self.grid[self.pos] + 1
        self.pos = (x, y)

        return self.grid[self.pos]

    def get_new_value(self):
        res = 0
        for dx, dy in self.deltas:
            if s := self.grid.get((self.pos[0] + dx, self.pos[1] + dy)):
                res += s
        self.grid[self.pos] = res
        return res


class Day03(Puzzle, year=2017, day=3):
    @staticmethod
    def clean_input(data: list[str]) -> list[str]:
        return data

    @timer(part=1)
    def solve_part_1(self) -> int:
        s = Spiral()
        target = int(self.data[0])

        for _ in range(2, target + 1):
            s.next_step()

        return Helpers.manhattan(s.pos)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        s = Spiral()
        target = int(self.data[0])

        while True:
            s.next_step()
            if s.get_new_value() > target:
                break

        return s.grid[s.pos]
