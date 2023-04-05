import re
import numpy as np
from common import timer, Puzzle


class Day06(Puzzle, year=2015, day=6):
    @staticmethod
    def clean_input(data):
        return_data = []
        for line in data:
            state, x0, y0, x1, y1 = re.findall(r"(on|off|toggle|\d+)", line)
            return_data.append(
                (state, (int(x0), int(x1) + 1), (int(y0), int(y1) + 1))
            )
        return return_data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        arr = np.zeros((1000, 1000), dtype=bool)

        for line in self.data:
            state = line[0]
            x = line[1]
            y = line[2]
            if state == "toggle":
                arr[y[0]:y[1], x[0]:x[1]] = np.logical_not(
                    arr[y[0]:y[1], x[0]:x[1]]
                )
            else:
                arr[y[0]:y[1], x[0]:x[1]] = state == "on"

        return len(arr[arr == np.True_])


    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        arr = np.zeros((1000, 1000))

        for line in self.data:
            state = line[0]
            x = line[1]
            y = line[2]
            if state == "toggle":
                arr[y[0]:y[1], x[0]:x[1]] += 2
            elif state == 'off':
                arr[y[0]:y[1], x[0]:x[1]] -= 1
            else:
                arr[y[0]:y[1], x[0]:x[1]] += 1

            arr[arr < 0] = 0
        return int(arr.sum())
