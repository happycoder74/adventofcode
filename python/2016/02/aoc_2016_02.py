import sys
from common import timer, get_input


class KeyPad:
    def __init__(self, alt_layout=False):
        self.alt_layout = alt_layout
        if not self.alt_layout:
            self.keypad = [['1', '2', '3'], ['4', '5', '6'], ['7', '8', '9']]
        else:
            self.keypad = [['0', '0', '1', '0', '0'],
                           ['0', '2', '3', '4', '0'],
                           ['5', '6', '7', '8', '9'],
                           ['0', 'A', 'B', 'C', '0'],
                           ['0', '0', 'D', '0', '0']]

        self.directions = {
            "U": (-1, 0), "D": (1, 0), "L": (0, -1), "R": (0, 1)
        }
        self.mx = len(self.keypad[0]) - 1
        self.pos = [2, 0] if self.alt_layout else [1, 1]
        self.code = []

    def get_code(self, data):
        for line in data:
            self.code.append(self.keystring(line))

        try:
            return ''. join([d for d in self.code])
        except TypeError:
            print(self.code)

    def key(self, key):
        diff = self.directions[key]
        pos = [self.pos[0] + diff[0], self.pos[1] + diff[1]]

        if self.digit(pos):
            return pos
        else:
            return self.pos

    def digit(self, pos):
        if (0 <= pos[0] <= self.mx) and (0 <= pos[1] <= self.mx):
            digit = self.keypad[pos[0]][pos[1]]
            if digit != '0':
                return digit
        return 0

    def keystring(self, keystring):
        for c in keystring:
            self.pos = self.key(c)
        return self.digit(self.pos)


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    kp = KeyPad()

    return kp.get_code(data)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    kp = KeyPad(alt_layout=True)

    return kp.get_code(data)


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2016, 2))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
