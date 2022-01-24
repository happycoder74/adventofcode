import sys
from common import timer, Parser


class DayParser(Parser):
    def __init__(self, year, day, filename="input.txt"):
        super().__init__(year, day, filename)
        self.data = DayParser.clean_input(self.data)

    @staticmethod
    def clean_input(data):
        return [[int(v) for v in x.split("x")] for x in data]


def aggfunc(x):
    w, l, h = x
    xx, yy = sorted(x)[:2]
    return 2*w*l + 2*l*h + 2*h*w + xx*yy


def ribbon(x):
    w, l, h = x
    xx, yy = sorted(x)[:2]
    return 2*xx + 2*yy + w*l*h


@timer(part=1)
def solve_part_1(data):
    """ Solution for part 1 """
    return sum(map(aggfunc, data))


@timer(part=2)
def solve_part_2(data):
    """ Solution for part 2 """
    return sum(map(ribbon, data))


@timer(part='main', title='Total time elapsed', show_return=False)
def main(filename):
    p = DayParser(2015, 2)

    part_1 = solve_part_1(p.data)
    part_2 = solve_part_2(p.data)

    return part_1, part_2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
