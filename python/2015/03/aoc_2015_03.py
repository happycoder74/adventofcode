import os
import sys
from common import timer


def get_input(filename):
    path = os.path.join(os.path.dirname(__file__), "../../../data/2015/03")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip()

    return clean_input(data)


def clean_input(data):
    return data


def solver(data, agents=1):
    delta = {"^": (1, 0), "v": (-1, 0), "<": (0, -1), ">": (0, 1)}
    pos = [(0, 0)] * agents
    visited = set()
    visited.add(pos[0])
    for index, c in enumerate(data):
        ind = index % agents
        dd = delta[c]
        pos[ind] = (pos[ind][0] + dd[0], pos[ind][1] + dd[1])
        visited.add(pos[ind])
        print(f"{index}, {ind} - ({pos[ind][1]}, {pos[ind][0]})")
    return len(visited)


@timer(part=1)
def solve_part_1(data):
    """ Solution for part 1 """
    return solver(data, 1)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return solver(data, 2)


@timer(part='main', title='Total elapsed', show_return=False)
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
