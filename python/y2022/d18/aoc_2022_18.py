import itertools
import operator
from common import timer, Puzzle


class Day18(Puzzle, year=2022, day=18):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.setup_grid()

    @staticmethod
    def clean_input(data):
        return [tuple(map(int, row.split(","))) for row in data]

    def setup_grid(self):
        self.limits = [
            (min(r[i] for r in self.data),
             max(r[i] for r in self.data)) for i in range(3)]

        self.grid = {k: 0 for k in itertools.product(
            range(self.limits[0][0] - 1, self.limits[0][1] + 2),
            range(self.limits[1][0] - 1, self.limits[1][1] + 2),
            range(self.limits[2][0] - 1, self.limits[2][1] + 2)
        )}

        for d in self.data:
            self.grid[d] = 1

    def surface_area(self, value=0):
        count = 0
        for pos in self.data:
            for neighbour in self.neighbours(pos):
                if self.grid[neighbour] == value:
                    count += 1
        return count

    def neighbours(self, position) -> list:
        delta = [
            (-1, 0, 0),
            (1, 0, 0),
            (0, -1, 0),
            (0, 1, 0),
            (0, 0, -1),
            (0, 0, 1),
        ]
        neighbour_list = []
        for d in delta:
            new_pos = tuple(map(operator.add, position, d))
            if new_pos in self.grid:
                neighbour_list.append(new_pos)

        return neighbour_list

    def find_trapped_surfaces(self):
        start_pos = (self.limits[0][0],
                     self.limits[1][0],
                     self.limits[2][0])
        self.grid[start_pos] = 2
        neighbour_list = []
        visited = [start_pos]

        for neighbour in self.neighbours(start_pos):
            if self.grid[neighbour] != 1:
                neighbour_list.append(neighbour)

        while neighbour_list:
            cube = neighbour_list.pop(0)
            if cube not in visited:
                visited.append(cube)
                if self.grid[cube] != 1:
                    self.grid[cube] = 2
                for neighbour in self.neighbours(cube):
                    if self.grid[neighbour] != 1:
                        neighbour_list.append(neighbour)

        return self.surface_area(value=2)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.surface_area()

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.find_trapped_surfaces()
