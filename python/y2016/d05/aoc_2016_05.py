import sys
import hashlib
from secrets import choice
from common import timer, get_input


def clean_input(data):
    return data


def find_code(doorID):
    code = ["_"] * 8
    index = 0
    position = 0
    while "_" in code:
        to_hash = f"{doorID}{index}".encode("utf-8")
        hashed = hashlib.md5(to_hash).hexdigest()
        if hashed[:5] == "00000":
            code[position] = hashed[5]
            position += 1
            print("".join(code), end="\r", flush=True)
        index += 1
    return "".join(code)


def find_code_2(doorID):
    code = ["_"] * 8
    index = 0
    scramble = "0123456789abcdef"
    try:
        while "_" in code:
            to_hash = f"{doorID}{index}".encode("utf-8")
            hashed = hashlib.md5(to_hash).hexdigest()
            if hashed[:5] == "00000":
                pos = int(hashed[5], 16)
                if pos < 8 and code[pos] == "_":
                    code[pos] = hashed[6]
            if (index - 1) % 1000 == 0:
                for pos in range(len(code)):
                    if code[pos] == "_":
                        print(
                            "\033[0;32m"
                            + choice(scramble)
                            + "\033[0m", end=""
                        )
                    else:
                        print(code[pos], end="")
                print("", end="\r", flush=True)

            index += 1
    except KeyboardInterrupt:
        print(index, "".join(code))
        return None
    else:
        return "".join(code)


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    return find_code(data[0])


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return find_code_2(data[0])


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2016, 5))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
