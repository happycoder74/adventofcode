import sys
from common import timer, get_input
from collections import Counter


def clean_input(data):
    return [list(d) for d in data]


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    return ''.join(
        [
            Counter(sublist).most_common(1)[0][0] for sublist in zip(*data)
        ])


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return ''.join(
        [
            Counter(sublist).most_common()[-1][0] for sublist in zip(*data)
        ])


@timer(part='main', title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2016, 6))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
