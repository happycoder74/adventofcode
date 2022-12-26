import re

from common import timer, Puzzle


class Day22(Puzzle, year=2022, day=22):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data, stripped=False)
        self.direction = (0, 1)
        self.position = (self.data[0][0].find("."), 0)
        self.directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        self.instructions = [(int(a), b) for a, b in re.findall(r"(\d+)(\w)", self.data[1][0])]
        self.grid = self.data[0]

    @staticmethod
    def clean_input(data):
        return_data = Puzzle.parse_input_groups(data)
        max_len = max([len(row) for row in return_data[0]])
        for i, row in enumerate(return_data[0]):
            if len(row) < max_len:
                padding = max_len - len(row)
                return_data[0][i] = (return_data[0][i] +
                                     ''.join([' ' for _ in range(padding)]))
        return return_data

    def turn(self, direction):
        index = self.directions.index(self.direction)
        if direction == 'R':
            index = (index - 1) % 4
        else:
            index = (index + 1) % 4
        self.direction = self.directions[index]

    def step(self, steps):
        for _ in range(steps):
            pos = tuple([self.position[i] + self.direction[i] for i in range(2)])
            if self.grid[pos[1]][pos[0]] != " " and self.grid[pos[1]][pos[0]] != '#':
                self.position = pos
            elif self.grid[pos[1]][pos[0]] == " ":
                # do something
                pass
            elif pos[1] == len(self.grid):
                pos = (0, pos[0])
                # Need to check for voids as well!
                if self.grid[pos[1]][pos[0]] == '#':
                    pos = self.position
            elif pos[1] < 0:
                pos = (len(self.grid) - 1, pos[0])
                # Need to check for voids as well!
                if self.grid[pos[1]][pos[0]] == '#':
                    pos = self.position
            elif pos[0] == len(self.grid[0]):
                pos = (pos[1], 0)
                # Need to check for voids as well!
                if self.grid[pos[1]][pos[0]] == '#':
                    pos = self.position
            elif pos[1] < 0:
                pos = (pos[1], len(self.grid[0]) - 1)
                # Need to check for voids as well!
                if self.grid[pos[1]][pos[0]] == '#':
                    pos = self.position
            self.position = pos

    def solve(self):
        for steps, turn in self.instructions:
            self.step(steps)
            self.turn(turn)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return None

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return None
