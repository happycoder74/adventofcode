import os
import sys
from common import timer


def get_input(filename):
    path = os.path.join(os.path.dirname(__file__), "../../../data/2015/01")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip()

    return clean_input(data)


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data):
    """ Solution for part 1 """
    return data.count("(") - data.count(")")


@timer(part=2)
def solve_part_2(data):
    """ Solution for part 2 """
    for i, c in enumerate(data):
        if data[:i].count("(") < data[:i].count(")"):
            return i
    return None


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = get_input(filename)

    part_1 = solve_part_1(data)
    part_2 = solve_part_2(data)

    return part_1, part_2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
