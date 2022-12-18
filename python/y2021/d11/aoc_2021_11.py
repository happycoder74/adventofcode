import sys
import numpy as np
from common import timer, get_input


def clean_input(data):
    return [[int(d) for d in line] for line in data]


def find_adj(cell, flashed, arr):
    x_c = cell[1]
    y_c = cell[0]

    neighbours = []
    if (x_c == 0) & (y_c == 0):
        neighbours.append((y_c + 1, x_c))
        neighbours.append((y_c + 1, x_c + 1))
        neighbours.append((y_c, x_c + 1))
    elif (x_c == 0) & (y_c == arr.shape[0] - 1):
        neighbours.append((y_c - 1, x_c))
        neighbours.append((y_c - 1, x_c + 1))
        neighbours.append((y_c, x_c + 1))
    elif (x_c == arr.shape[1] - 1) & (y_c == 0):
        neighbours.append((y_c + 1, x_c))
        neighbours.append((y_c + 1, x_c - 1))
        neighbours.append((y_c, x_c - 1))
    elif (x_c == arr.shape[1] - 1) & (y_c == arr.shape[0] - 1):
        neighbours.append((y_c - 1, x_c))
        neighbours.append((y_c - 1, x_c - 1))
        neighbours.append((y_c, x_c - 1))
    elif (x_c == 0) | (x_c == arr.shape[1] - 1):
        neighbours.append(((y_c + 1), (x_c)))
        neighbours.append(((y_c - 1), (x_c)))
        direction = 1 if x_c == 0 else -1
        neighbours.append(((y_c + 1), (x_c + direction)))
        neighbours.append((y_c, (x_c + direction)))
        neighbours.append(((y_c - 1), (x_c + direction)))
    elif (y_c == 0) | (y_c == arr.shape[0] - 1):
        neighbours.append((y_c, (x_c - 1)))
        neighbours.append((y_c, (x_c + 1)))
        direction = 1 if y_c == 0 else -1
        neighbours.append(((y_c + direction), (x_c - 1)))
        neighbours.append(((y_c + direction), (x_c)))
        neighbours.append(((y_c + direction), (x_c + 1)))
    else:
        neighbours.append((y_c - 1, x_c - 1))
        neighbours.append((y_c - 1, x_c))
        neighbours.append((y_c - 1, x_c + 1))
        neighbours.append((y_c, x_c - 1))
        neighbours.append((y_c, x_c + 1))
        neighbours.append((y_c + 1, x_c - 1))
        neighbours.append((y_c + 1, x_c))
        neighbours.append((y_c + 1, x_c + 1))

    return neighbours


@timer(part=1)
def solve_part_1(data, steps):
    """Solution for part 1"""
    arr = np.array(data)
    total_flashed = []
    for step in range(0, steps):
        arr = arr + 1
        flashed = []
        while (arr > 9).any():
            new_flash = []
            for y_c, row in enumerate(arr):
                for x_c, col in enumerate(row):
                    if arr[y_c, x_c] > 9:
                        new_flash.append((y_c, x_c))
                        arr[y_c, x_c] = 0

            flashed = flashed + new_flash
            for y, x in new_flash:
                neighbours = find_adj((y, x), flashed, arr)
                for (yc, xc) in neighbours:
                    if (yc, xc) not in flashed:
                        arr[yc][xc] += 1
        total_flashed.append(flashed)

    number_of_flashes = sum([len(flashed) for flashed in total_flashed])
    return number_of_flashes


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    arr = np.array(data)
    total_flashed = []
    all_flashed = False
    step = 0
    while (not all_flashed):
        arr = arr + 1
        flashed = []
        while (arr > 9).any():
            new_flash = []
            for y_c, row in enumerate(arr):
                for x_c, col in enumerate(row):
                    if arr[y_c, x_c] > 9:
                        new_flash.append((y_c, x_c))
                        arr[y_c, x_c] = 0

            flashed = flashed + new_flash
            for y, x in new_flash:
                neighbours = find_adj((y, x), flashed, arr)
                for (yc, xc) in neighbours:
                    if (yc, xc) not in flashed:
                        arr[yc][xc] += 1
        total_flashed.append(flashed)

        all_flashed = (arr == 0).all()
        step += 1
    return step


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 11))

    part1 = solve_part_1(data, steps=100)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
