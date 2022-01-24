import os
import re
import sys
from common import timer


def get_input(filename):
    path = os.path.join(os.path.dirname(__file__), "../../../data/2016/7")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip().splitlines()

    return clean_input(data)


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    abba = re.compile(r"(\w)((?!\1)\w)\2\1")
    hypernet = re.compile(r"(\[\w+\])")

    count = 0
    for line in data:
        match_found = False
        inside_hypernet = False
        for m in abba.finditer(line):
            match_found = True
            for match in hypernet.finditer(line):
                if m.group(0) in match.group(0):
                    inside_hypernet = True
        if not inside_hypernet and match_found:
            count += 1

    return count


def find_aba_bab(line, aba, hypernet):
    supernet_str = '|'.join(re.split(r'\[\w+\]', line))
    hypernet_str = ''.join([m.group(0) for m in hypernet.finditer(line)])

    aba_matches = [m.group(1) for m in aba.finditer(supernet_str)]
    for m in aba_matches:
        bab = m[1] + m[0] + m[1]
        if bab in hypernet_str:
            return True
    return False


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    aba = re.compile(r"(?=((\w)((?!\2)\w)\2))")
    hypernet = re.compile(r"(\[\w+\])")

    matching_lines = []
    for line in data:
        if find_aba_bab(line, aba, hypernet):
            matching_lines.append(line)

    return len(matching_lines)


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
