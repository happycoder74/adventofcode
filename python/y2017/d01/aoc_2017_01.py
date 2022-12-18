import sys
from common import timer, get_input


def clean_input(data):
    return data[0]


@timer(part=1)
def solve_part_1(data, step=1):
    """Solution for part 1"""

    return sum(
        [
            int(c1)
            for c1, c2 in zip(data, f"{data[step:]}{data[:step]}")
            if c1 == c2
        ]
    )


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return solve_part_1(data, len(data) // 2)


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2017, 1))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
