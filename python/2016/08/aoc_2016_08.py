import re
import sys
import time
import numpy as np
from common import timer, get_input


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


def create_display(data, animate=False):
    arr = np.zeros((6, 50), dtype=int)
    for command, x, y in data:
        if command == 'rect':
            arr[0:y, 0:x] = 1
        elif command == 'col':
            arr[:, x] = np.roll(arr[:, x], y)
        elif command == 'row':
            arr[x, :] = np.roll(arr[x, :], y)
        if animate:
            for row in arr:
                print(''.join([
                    chr(int('2593', 16)) if val == 1 else ' ' for val in row
                ]))
            print("\r\033[7A")
        time.sleep(0.04)
    print("\033[7B")
    return arr


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""

    return sum(sum(create_display(data, animate=True)))


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""

    return chr(int('261D', 16))


def main(filename):
    data = clean_input(get_input(filename, 2016, 8))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
