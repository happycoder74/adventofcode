import sys
from common import timer, get_input


def clean_input(data):
    return [int(d) for d in data]


@timer(part=1)
def solve_part_1(data, window=1):
    """ Solution for part 1 """
    return len([(a, b) for a, b in zip(data, data[window:]) if b > a])


@timer(part=2)
def solve_part_2(data):
    """ Solution for part 2 """
    return solve_part_1(data, window=3)


@timer(part="main", title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 1))

    part_1 = solve_part_1(data)
    part_2 = solve_part_2(data)

    return part_1, part_2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
