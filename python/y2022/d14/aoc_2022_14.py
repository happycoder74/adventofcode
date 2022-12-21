from collections import defaultdict
from common import timer, Puzzle


class Day14(Puzzle, year=2022, day=14):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.setup_grid()

    @staticmethod
    def clean_input(data: list) -> list:
        return data

    def setup_grid(self) -> None:
        self.grid: defaultdict = defaultdict(lambda: '.')
        wall_points: set = set()
        for row in self.data:
            points = [tuple(map(int, point.split(",")))
                      for point in row.split(" -> ")]
            for p1, p2 in zip(points[:-1], points[1:]):
                step = tuple([1 if p1[i] <= p2[i] else -1 for i in range(2)])
                wall_points = wall_points.union(
                    set([(x, y)
                         for x in range(p1[0], p2[0] + step[0], step[0])
                         for y in range(p1[1], p2[1] + step[1], step[1])
                         ])
                )
        for p in wall_points:
            self.grid[p] = "#"

        self.max_x = max(x for x, y in wall_points)
        self.max_y = max(y for x, y in wall_points)
        self.min_x = min(x for x, y in wall_points)
        self.min_y = min(y for x, y in wall_points)

    def print_grid(self):
        self.max_x = max(x for x, y in self.grid.keys())
        self.max_y = max(y for x, y in self.grid.keys())
        self.min_x = min(x for x, y in self.grid.keys())
        self.min_y = min(y for x, y in self.grid.keys())

        print(f"{self.min_x=}\n{self.max_x=}\n{self.min_y=}\n{self.max_y=}")

        for y in range(self.min_y, self.max_y + 1):
            row = list()
            for x in range(self.min_x, self.max_x + 1):
                if not self.grid[(x, y)]:
                    row.append('.')
                else:
                    row.append(self.grid[(x, y)])
            print("{} {}".format(y, ''.join(row)))

    def solver(self, part: int = 1):
        flowing: bool = False
        blocked: bool = False
        grain_count: int = sum([1 for p in self.grid.values() if p == "o"])
        try:
            while (not flowing) and (not blocked):
                grain_pos: tuple = (500, 0)
                while True:
                    if (self.grid[500, 0] == "o") and part == 2:
                        blocked = True
                        break
                    new_pos: tuple = (grain_pos[0], grain_pos[1] + 1)
                    if self.grid[new_pos] in ["#", "o"]:
                        new_pos = (grain_pos[0] - 1, grain_pos[1] + 1)
                    if self.grid[new_pos] in ["#", "o"]:
                        new_pos = (grain_pos[0] + 1, grain_pos[1] + 1)
                    if self.grid[new_pos] in ["#", "o"]:
                        grain_count += 1
                        self.grid[grain_pos] = "o"
                        break
                    if part == 1:
                        if new_pos[1] > self.max_y:
                            flowing = True
                            break
                    else:
                        if new_pos[1] == self.max_y + 1:
                            grain_pos = new_pos
                            self.grid[grain_pos] = "o"
                            grain_count += 1
                            break
                    grain_pos = new_pos
        except KeyboardInterrupt:
            print(f"{grain_count=}")
            self.print_grid()
            return None

        return grain_count

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        return self.solver()

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.solver(part=2)
