import sys
from collections import OrderedDict
from common import timer, Puzzle, sign


class Day9(Puzzle, year=2022, day=9):

    @staticmethod
    def clean_input(data):
        return [(r.split()[0], int(r.split()[1])) for r in data]

    @staticmethod
    def is_contact(t_pos, h_pos):
        zone = [(h_pos[0] + x, h_pos[1] + y)
                for x in range(-1, 2) for y in range(-1, 2)]
        if t_pos not in zone:
            return False
        return True

    def print_rope(self, rope):
        for y in range(15, -6, -1):
            for x in range(-11, 15):
                if (x, y) in rope:
                    number = rope.index((x, y))
                    if number == 0:
                        print("H", end="")
                    else:
                        print(number, end="")
                elif ((x, y) == (0, 0)):
                    print("s", end="")
                else:
                    print(".", end="")
            print("")

    def print_map(self, visited):
        max_x = 15
        min_x = -11
        max_y = 15
        min_y = -6
        for row in range(max_y, min_y, -1):
            for col in range(min_x, max_x):
                if((col, row) == (0, 0)):
                    print("s", end="")
                elif ((col, row) in visited):
                    print("#", end="")
                else:
                    print(".", end="")
            print("")

    @staticmethod
    def in_column(pos1: tuple, pos2: tuple) -> bool:
        return pos1[0] == pos2[0]

    @staticmethod
    def in_row(pos1: tuple, pos2: tuple) -> bool:
        return pos1[1] == pos2[1]

    def rope(self, length=2):
        pos = [(0, 0)] * length
        visited = OrderedDict()
        step = {'R': (1, 0), 'L': (-1, 0), 'U': (0, 1), 'D': (0, -1)}
        for counter, row in enumerate(self.data):
            move = step[row[0]]
            for c in range(row[1]):
                pos[0] = (pos[0][0] + move[0],
                          pos[0][1] + move[1])
                for i in range(1, length):
                    delta_x = (pos[i - 1][0] - pos[i][0])
                    delta_y = (pos[i - 1][1] - pos[i][1])
                    if Day9.in_column(pos[i], pos[i - 1]) and abs(delta_y) > 1:
                        delta = (0, sign(delta_y))
                    elif Day9.in_row(pos[i], pos[i - 1]) and abs(delta_x) > 1:
                        delta = (sign(delta_x), 0)
                    elif (abs(delta_x) + abs(delta_y) > 2):
                        delta = (sign(delta_x), sign(delta_y))
                    else:
                        delta = (0, 0)
                    pos[i] = (pos[i][0] + delta[0],
                              pos[i][1] + delta[1])
                visited[pos[-1]] = None
        return len(visited)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.rope(length=2)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.rope(length=10)


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day9(filename=filename).solve_all()
