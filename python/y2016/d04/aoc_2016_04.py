import re
import string
import sys
from collections import Counter
from common import timer, get_input


def clean_input(data):
    return data


def validate_room(room_info):
    c = Counter(room_info[0])
    sectorID = int(room_info[1])
    checksum = room_info[2]

    _ = c.pop('-')
    most_common = "".join(
        x[0] for x in sorted(c.items(), key=lambda x: (-x[1], x[0]))
    )

    return sectorID if most_common[:5] == checksum else 0


def decrypt(room_info):
    decrypted = []
    letters = string.ascii_lowercase
    len_letters = len(letters)
    for c in room_info[0]:
        if c == "-":
            decrypted.append(" ")
        else:
            ind = letters.index(c) + int(room_info[1])
            decrypted.append(letters[ind % len_letters])

    return "".join(decrypted)


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    pattern = re.compile(r"((?:\w+\-)+)(\d+)\[(\w+)\]")
    split_room_info = [x.groups() for x in map(pattern.match, data)]
    return sum([validate_room(room_info) for room_info in split_room_info])


@timer(part=2)
def solve_part_2(data, check_string="northpole"):
    """Solution for part 2"""
    pattern = re.compile(r"((?:\w+\-)+)(\d+)\[(\w+)\]")
    for room in data:
        split_room_info = pattern.match(room).groups()
        if validate_room(split_room_info) != 0:
            if check_string in decrypt(split_room_info):
                return int(re.findall(r"(\d+)", room)[0])
    return None


@timer(part="", title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2016, 4))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
