import numpy as np
import sys
from common import timer, get_input


def clean_input(data):
    data = [int(num.strip()) for num in data]
    return np.array(data)


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    for num in data:
        rest = data[data >= (2020 - num)]
        for n in rest:
            if n + num == 2020:
                return n * num
    return None


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    for num1 in data:
        for num2 in data[data > num1]:
            rest = data[data >= (2020 - num1 - num2)]
            for n in rest:
                if n + num1 + num2 == 2020:
                    return n * num1 * num2
    return None


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2020, 1))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
