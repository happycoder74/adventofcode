import re
import sys
from common import timer, get_input


def clean_input(data):
    return data


def check_wovels(line):
    return len(re.findall(r"[aeiou]", line)) >= 3


def check_dbl_letter(line):
    return len(re.findall(r"(.)\1", line)) > 0


def check_invalid(line):
    pattern = r"(ab|cd|pq|xy)"
    return len(re.findall(pattern, line)) == 0


def check_pairs(line):
    pattern = r"([a-z][a-z])\w*\1"
    return len(re.findall(pattern, line)) > 0


def check_repeat(line):
    pattern = r"(.)\w\1"
    return len(re.findall(pattern, line)) > 0


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    valid_lines = 0
    for line in data:
        if (
            check_wovels(line)
            and check_dbl_letter(line)
            and check_invalid(line)
        ):
            valid_lines += 1
    return valid_lines


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    valid_lines = 0
    for line in data:
        if check_pairs(line) and check_repeat(line):
            valid_lines += 1
    return valid_lines


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2015, 5))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
