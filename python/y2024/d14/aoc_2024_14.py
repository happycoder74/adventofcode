import functools
import operator
from collections import Counter
from dataclasses import dataclass

from common import Puzzle, timer


@dataclass
class Robot:
    pos_x: int
    pos_y: int
    vel_x: int
    vel_y: int
    max_x: int
    max_y: int

    @property
    def mid_x(self):
        return self.max_x // 2

    @property
    def mid_y(self):
        return self.max_y // 2

    def move(self, steps=1):
        self.pos_x = (self.pos_x + self.vel_x * steps) % self.max_x
        self.pos_y = (self.pos_y + self.vel_y * steps) % self.max_y

    @property
    def quadrant(self):
        if self.pos_x < self.mid_x:
            if self.pos_y < self.mid_y:
                return "TL"
            elif self.pos_y > self.mid_y:
                return "BL"
        elif self.pos_x > self.mid_x:
            if self.pos_y < self.mid_y:
                return "TR"
            elif self.pos_y > self.mid_y:
                return "BR"
        return "M"


class Bathroom:
    def __init__(self, robots, max_x, max_y):
        self.max_x = max_x
        self.max_y = max_y

        self.robots = [Robot(*l, max_x=max_x, max_y=max_y) for l in robots]
        self.unique_positions = Counter((r.pos_x, r.pos_y) for r in self.robots)

    def move_robots(self, steps=1):
        for robot in self.robots:
            self.unique_positions[(robot.pos_x, robot.pos_y)] -= 1
            robot.move(steps)
            self.unique_positions[(robot.pos_x, robot.pos_y)] += 1

    def safety_factor(self):
        c = Counter(robot.quadrant for robot in self.robots)
        c.pop("M", None)
        return functools.reduce(operator.mul, c.values(), 1)

    def is_christmas_tree(self):
        # Check if all robots are on a unique position
        # This isn't necessarily the solution but for me it was
        return self.unique_positions.most_common(1)[0][1] == 1

    def print_room(self):
        for r in range(self.max_y):
            row = []
            for c in range(self.max_x):
                if self.unique_positions[(c, r)] > 0:
                    row.append("#")
                else:
                    row.append(".")
            print("".join(row))


class Day14(Puzzle, year=2024, day=14):
    @staticmethod
    def clean_input(data) -> list:
        d = [line[2:].split(" v=") for line in data]
        return [(tuple(map(int, v1.split(",") + v2.split(",")))) for v1, v2 in d]

    @timer(part=1)
    def solve_part_1(self) -> int:
        nrows = 103
        ncolumns = 101
        if max(max(self.data)) <= 10:
            nrows = 7
            ncolumns = 11
        br = Bathroom(robots=self.data, max_x=ncolumns, max_y=nrows)
        br.move_robots(steps=100)
        return br.safety_factor()

    @timer(part=2)
    def solve_part_2(
        self,
    ) -> int:
        nrows = 103
        ncolumns = 101
        if max(max(self.data)) <= 10:
            nrows = 7
            ncolumns = 11
        br = Bathroom(robots=self.data, max_x=ncolumns, max_y=nrows)

        step = 0
        while not br.is_christmas_tree():
            step += 1
            br.move_robots()
            if step % 100 == 0:
                print(".", end="", flush=True)

        print()
        br.print_room()
        return step
