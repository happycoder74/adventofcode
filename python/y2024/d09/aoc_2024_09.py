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
            for _ in range(blocks[1]):
                checksum += counter * blocks[0]
                counter += 1
        return checksum

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        self.new_layout = list(self.data)

        length = len(self.new_layout)
        index = length - 1
        while index > 0:
            last_item = self.new_layout[index]
            for ii in range(0, index):
                item = self.new_layout[ii]
                if item[1][1] >= last_item[1][0]:
                    move_item = self.new_layout.pop(index)
                    self.new_layout.insert(
                        ii + 1,
                        (move_item[0], (move_item[1][0], item[1][1] - move_item[1][0])),
                    )
                    self.new_layout[ii] = (item[0], (item[1][0], 0))
                    corr_item = self.new_layout[index]
                    self.new_layout[index] = (
                        corr_item[0],
                        (corr_item[1][0], corr_item[1][1] + sum(last_item[1])),
                    )
                    index += 1
                    break
            index -= 1

        counter = 0
        checksum = 0
        for blocks in self.new_layout:
            for _ in range(blocks[1][0]):
                checksum += counter * blocks[0]
                counter += 1
            counter += blocks[1][1]
        return checksum
