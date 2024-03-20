import re
import time

import numpy as np
from common import Puzzle, timer


class Day08(Puzzle, year=2016, day=8):
    @staticmethod
    def clean_input(data):
        rect = re.compile(r"(\d+)x(\d+)")
        rotate = re.compile(r"(\d+) by (\d+)")

        commands = []
        for line in data:
            command = None
            if line.startswith("rect"):
                m = rect.findall(line)
                command = ("rect", int(m[0][0]), int(m[0][1]))
            elif line.startswith("rotate"):
                m = rotate.findall(line)
                for direction in ["col", "row"]:
                    if direction in line:
                        command = (direction, int(m[0][0]), int(m[0][1]))
            if command:
                commands.append(command)

        return commands

    def create_display(self, animate=False):
        arr = np.zeros((6, 50), dtype=int)
        for command, x, y in self.data:
            if command == "rect":
                arr[0:y, 0:x] = 1
            elif command == "col":
                arr[:, x] = np.roll(arr[:, x], y)
            elif command == "row":
                arr[x, :] = np.roll(arr[x, :], y)
            if animate:
                for row in arr:
                    print("".join([chr(int("2593", 16)) if val == 1 else " " for val in row]))
                print("\r\033[7A")
            time.sleep(0.01)
        print("\033[7B")
        return arr

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""

        return np.sum(self.create_display(animate=True))

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""

        return chr(int("261D", 16))
