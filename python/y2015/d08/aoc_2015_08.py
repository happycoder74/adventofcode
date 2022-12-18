import re
import sys
from common import timer, get_input


def clean_input(data):
    return data


def clean(pattern, line):
    match = pattern.search(line)
    if match:
        line = 'A'.join(re.split(pattern, line))
    return line


def clean_hex(line):
    pattern = re.compile(r"\\x[0-9, a-f]{2}")
    return clean(pattern, line)


def clean_escaped_quote(line):
    pattern = re.compile(r'\\\"')
    return clean(pattern, line)


def clean_escaped_backslash(line):
    pattern = re.compile(r'\\\\')
    return clean(pattern, line)


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    cleaned = []
    for line in data:
        if line[0] == '"':
            line = line[1:]
        if line[-1] == '"':
            line = line[:-1]
        line = clean_hex(line)
        line = clean_escaped_quote(line)
        line = clean_escaped_backslash(line)

        cleaned.append(line)

    return sum([len(s) for s in data]) - sum([len(s) for s in cleaned])


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    escaped = []
    for line in data:
        line = line.replace('\\', '\\\\')
        line = line.replace('"', '\\"')

        escaped.append(f'"{line}"')

    return sum([len(s) for s in escaped]) - sum([len(s) for s in data])


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2015, 8))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
