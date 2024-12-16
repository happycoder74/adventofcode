from collections import deque
from itertools import zip_longest

from common import Puzzle, timer


class Day09(Puzzle, year=2024, day=9):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.disk = deque(self.data)
        self.new_layout = list()

    @staticmethod
    def clean_input(data) -> list:
        input = data[0].strip()
        return [
            (index, (int(v1), int(v2))) if v2 is not None else (index, (int(v1), 0))
            for index, (v1, v2) in enumerate(zip_longest(input[::2], input[1::2]))
        ]

    def print_layout(self):
        for block in self.new_layout:
            for _ in range(block[1]):
                print(block[0], end="")
        for index, (c, s) in self.disk:
            for _ in range(c):
                print(index, end="")
            for sp in range(s):
                print(".", end="")

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        checksum = 0
        while self.disk:
            item = self.disk.popleft()
            self.new_layout.append((item[0], item[1][0]))
            if not self.disk:
                break
            last_item = self.disk.pop()
            available = item[1][1] - last_item[1][0]
            if available == 0:
                self.new_layout.append((last_item[0], last_item[1][0]))
            elif available < 0:
                self.new_layout.append((last_item[0], last_item[1][0] + available))
                last_item = (
                    last_item[0],
                    (-available, last_item[1][1] + last_item[1][0] + available),
                )
                self.disk.append(last_item)

            else:
                while available >= 0:
                    self.new_layout.append((last_item[0], last_item[1][0]))
                    last_item = self.disk.pop()
                    available -= last_item[1][0]
                self.new_layout.append((last_item[0], last_item[1][0] + available))
                self.disk.append((last_item[0], (-available, last_item[1][1])))

        print("", end="\n")
        counter = 0
        for blocks in self.new_layout:
            for c in range(blocks[1]):
                checksum += counter * blocks[0]
                counter += 1
        return checksum

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        result = 0

        return result
