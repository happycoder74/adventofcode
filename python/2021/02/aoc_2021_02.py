import sys
from common import timer, get_input


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    commands = dict(
        forward=0,
        down=0,
        up=0)
    for line in data:
        parts = line.split()
        commands[parts[0]] += int(parts[1])

    return commands["forward"] * (commands["down"] - commands["up"])


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    horizontal = 0
    aim = 0
    depth = 0
    for line in data:
        parts = line.split()
        if parts[0] == 'forward':
            horizontal += int(parts[1])
            depth += aim*int(parts[1])
        if parts[0] == 'down':
            aim += int(parts[1])
        if parts[0] == 'up':
            aim -= int(parts[1])

    return horizontal * depth


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 2))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
