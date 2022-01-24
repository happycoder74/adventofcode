import os
import sys
from common import timer


def get_input(filename):
    path = os.path.join(os.path.dirname(__file__), "../../../data/year/day")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip().splitlines()

    return clean_input(data)


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    return None


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return None


@timer(part='main', title='Total elapsed', show_return=False)
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
