import itertools
import sys
from common import timer, get_input


def clean_input(data):
    return data[0]


def look_and_say(line):
    s = ''
    groups = [''.join(g) for _, g in itertools.groupby(line)]
    for g in groups:
        s += f"{g.count(g[0])}{g[0]}"

    return s


@timer(part=1)
def solve_part_1(data, loops=40):
    """Solution for part 1"""
    line = data
    for loop in range(loops):
        line = look_and_say(line)

    return len(line)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""

    return solve_part_1(data, loops=50)


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2015, 10))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
