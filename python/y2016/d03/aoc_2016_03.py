import sys
from common import timer, get_input


def clean_input(data):
    return [tuple(map(int, line.split())) for line in data]


def count_valid(data):
    return len(
        list(
            filter(
                lambda x: (
                    (x[0] + x[1] > x[2])
                    and (x[1] + x[2] > x[0])
                    and (x[2] + x[0] > x[1])
                ),
                data,
            )
        )
    )


def convert_data(data):
    return [
        (data[i][col], data[i + 1][col], data[i + 2][col])
        for col in range(3)
        for i in range(0, len(data[:-2]), 3)
    ]


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    return count_valid(data)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return count_valid(convert_data(data))


@timer(part="", title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2016, 3))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
