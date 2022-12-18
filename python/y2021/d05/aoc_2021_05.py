import sys
import numpy as np
from common import timer, get_input


def clean_input(data):
    data = list(map(lambda x: x.split("->"), data))
    data = [
        [
            (
                int(item[0].strip().split(",")[0]),
                int(item[0].strip().split(",")[1]),
            ),
            (
                int(item[1].strip().split(",")[0]),
                int(item[1].strip().split(",")[1]),
            ),
        ]
        for item in data
    ]
    return data


def is_horizontal(line):
    return line[0][1] == line[1][1]


def is_vertical(line):
    return line[0][0] == line[1][0]


def is_diagonal(line):
    """Find if line is diagonal"""
    return abs(line[0][0] - line[1][0]) == abs(line[0][1] - line[1][1])


def mark_line(field, line):
    """Mark line in field"""
    x0 = line[0][0]
    x1 = line[1][0]
    y0 = line[0][1]
    y1 = line[1][1]
    stepx = 1 if x1 >= x0 else -1
    stepy = 1 if y1 >= y0 else -1
    if is_horizontal(line):
        x = list(range(x0, x1 + stepx, stepx))
        y = list([y0]) * len(x)
    if is_vertical(line):
        y = list(range(y0, y1 + stepy, stepy))
        x = list([x0]) * len(y)
    if is_diagonal(line):
        x = list(range(x0, x1 + stepx, stepx))
        y = list(range(y0, y1 + stepy, stepy))
    for index, _ in enumerate(x):
        field[y[index], x[index]] += 1
    return field


def create_field(data):
    xspan = [0, 0]
    yspan = [0, 0]
    for line in data:
        xspan[0] = min(xspan[0], line[0][0], line[1][0])
        xspan[1] = max(xspan[1], line[0][0], line[1][0])
        yspan[0] = min(yspan[0], line[0][1], line[1][1])
        yspan[1] = max(yspan[1], line[0][1], line[1][1])

    field = np.zeros((max(yspan) + 1, max(xspan) + 1))
    return field


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    field = create_field(data)

    for line in data:
        x0 = min(line[0][0], line[1][0])
        x1 = max(line[0][0], line[1][0])
        y0 = min(line[0][1], line[1][1])
        y1 = max(line[0][1], line[1][1])
        if (x0 == x1) | (y0 == y1):
            field[y0:y1+1, x0:x1+1] += 1

    return (field > 1).sum()


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    field = create_field(data)

    for line in data:
        if is_vertical(line) | is_horizontal(line) | is_diagonal(line):
            try:
                field = mark_line(field, line)
            except IndexError as err:
                print(f"Index error at line {line}")
                print(err)
                sys.exit(1)

    return (field > 1).sum()


@timer(part="main", title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 5))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
