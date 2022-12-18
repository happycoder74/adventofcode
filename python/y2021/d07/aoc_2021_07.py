import sys
import numpy as np
from common import timer, get_input


def clean_input(data):
    return np.array([int(num) for num in data[0].split(',')])


def calc_fuel(data, pos, part):
    if part == 1:
        return sum(abs(data - pos))
    else:
        return sum([sum(range(abs(d - pos) + 1)) for d in data])


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    min_pos = min(data)
    min_fuel = calc_fuel(data, min_pos, part=1)
    print(f"{min_pos=}, {min_fuel=}")

    for pos in data:
        fuel = calc_fuel(data, pos, part=1)
        if fuel < min_fuel:
            min_fuel = fuel
            min_pos = pos
    return min_fuel


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    min_pos = min(data)
    min_fuel = calc_fuel(data, min_pos, part=2)

    for pos in range(0, max(data)+1):
        fuel = calc_fuel(data, pos, part=2)
        if fuel < min_fuel:
            min_fuel = fuel
            min_pos = pos
    return min_fuel


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 7))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
