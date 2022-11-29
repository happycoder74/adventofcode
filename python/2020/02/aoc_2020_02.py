import re
import sys
from common import timer, get_input


def clean_input(data):
    data = [val.split(' ') for val in data]
    return data


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    found = 0
    for p in data:
        pattern = fr"{p[1][:-1]}"
        matches = re.findall(pattern, p[2])
        limits = [int(val) for val in p[0].split('-')]
        if (len(matches) >= limits[0]) & (len(matches) <= limits[1]):
            found += 1

    return found


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    found = 0
    for p in data:
        pattern = f"{p[1][:-1]}"
        limits = [int(val) - 1 for val in p[0].split('-')]
        if (p[2][limits[0]] == pattern) ^ (p[2][limits[1]] == pattern):
            found += 1

    return found


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2020, 2))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
