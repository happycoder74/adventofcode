import re
import sys
import numpy as np
from common import timer, get_input


def clean_input(data):
    return_data = []
    for line in data:
        state, x0, y0, x1, y1 = re.findall(r"(on|off|toggle|\d+)", line)
        return_data.append(
            (state, (int(x0), int(x1) + 1), (int(y0), int(y1) + 1))
        )
    return return_data


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    arr = np.zeros((1000, 1000), dtype=bool)

    for line in data:
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
def solve_part_2(data):
    """Solution for part 2"""
    arr = np.zeros((1000, 1000))

    for line in data:
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


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2015, 6))

    part_1 = solve_part_1(data)
    part_2 = solve_part_2(data)

    return part_1, part_2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
