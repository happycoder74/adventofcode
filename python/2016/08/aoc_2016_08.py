import os
import re
import sys
import numpy as np
from common import timer


def get_input(filename):
    path = os.path.join(os.path.dirname(__file__), "../../../data/2016/8")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip().splitlines()

    return clean_input(data)


def clean_input(data):
    rect = re.compile(r'(\d+)x(\d+)')
    rotate = re.compile(r'(\d+) by (\d+)')

    commands = []
    for line in data:
        if line.startswith('rect'):
            m = rect.findall(line)
            command = ('rect', int(m[0][0]), int(m[0][1]))
        elif line.startswith('rotate'):
            m = rotate.findall(line)
            for direction in ['col', 'row']:
                if direction in line:
                    command = (direction, int(m[0][0]), int(m[0][1]))
        commands.append(command)

    return commands


def create_display(data):
    arr = np.zeros((6, 50), dtype=int)
    for command, x, y in data:
        if command == 'rect':
            arr[0:y, 0:x] = 1
        elif command == 'col':
            arr[:, x] = np.roll(arr[:, x], y)
        elif command == 'row':
            arr[x, :] = np.roll(arr[x, :], y)
    return arr


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""

    return sum(sum(create_display(data)))


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""

    arr = create_display(data)

    for row in arr:
        print(''.join([chr(int('2593', 16)) if val == 1 else ' ' for val in row]))

    return None


def main(filename):
    data = get_input(filename)

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
