import sys
from common import timer, get_input


def clean_input(data):
    return [(d[0], int(d[1:])) for d in data[0].split(", ")]


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

    current = directions[0]
    pos = (0, 0)
    for direction, steps in data:
        ind = directions.index(current) + (1 if direction == 'R' else -1)
        ind = ind % 4 if ind > 0 else ind % -4
        current = directions[ind]
        pos = (pos[0] + steps*current[0], pos[1] + steps*current[1])

    return abs(pos[0]) + abs(pos[1])


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]

    current = directions[0]
    pos = (0, 0)
    locations = set()
    locations.add(pos)
    for direction, steps in data:
        ind = (directions.index(current) + (1 if direction == 'R' else -1)) % 4
        current = directions[ind]
        for _ in range(steps):
            pos = (pos[0] + current[0], pos[1] + current[1])
            if pos in locations:
                return abs(pos[0]) + abs(pos[1])
            locations.add(pos)

    return None


@timer(part="Total", show_result=False)
def main(filename):
    data = clean_input(get_input(filename, 2016, 1))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
