import hashlib
import os
import sys
from common import timer


def get_input(filename):
    path = os.path.join(os.path.dirname(__file__), "../../../data/2015/04")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip()

    return clean_input(data)


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data, zeros=5):
    """ Solution for part 1 """
    number = 0
    z = "0" * zeros
    hashcode = ''
    while not hashcode.startswith(z):
        number += 1
        string = f"{data}{number}".encode('utf-8')
        hashcode = hashlib.md5(string).hexdigest()

    return number


@timer(part=2)
def solve_part_2(data):
    """ Solution for part 2 """
    return solve_part_1(data, zeros=6)


@timer(part='main', title="Total elapsed", show_result=False)
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
