import re
from common import timer, Puzzle


class Day15(Puzzle, year=2022, day=15):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.grid = dict()
        self.setup_grid()

    @staticmethod
    def clean_input(data):
        sensors = {}
        for row in data:
            x, y, xx, yy = list(map(int, re.findall(pattern=r"\w*=(-{0,1}\d+)", string=row)))
            sensors[(x, y)] = {'beacon': (xx, yy), 'distance': (abs(x - xx) + abs(y - yy))}

        return sensors

    def setup_grid(self):
        for pos, beacon in self.data.items():
            self.grid[pos] = 'S'
            self.grid[beacon['beacon']] = 'B'

    def print_grid(self):
        limits_x = (min(p[0] for p in self.grid.keys()),
                    max(p[0] for p in self.grid.keys()))
        limits_y = (min(p[1] for p in self.grid.keys()),
                    max(p[1] for p in self.grid.keys()))
        for row in range(limits_y[0], limits_y[1] + 1):
            print(f"{row:4d}", end="")
            for col in range(limits_x[0], limits_x[1] + 1):
                if self.grid.get((col, row), ' ') in ['S', 'B', '#']:
                    print(self.grid.get((col, row), ' '), end="")
                else:
                    print(".", end="")
            print()

    @timer(part=1)
    def solve_part_1(self, row=2000000):
        """Solution for part 1"""
        blocked_pos_list = set()
        for (x, y), beacon in self.data.items():
            if (y - beacon['distance']) <= row <= (y + beacon['distance']):
                yy = list(range(y - beacon['distance'], y + beacon['distance'] + 1))
                xx = beacon['distance'] - abs(yy[yy.index(row)] - y)
                for dx in range(-xx, xx + 1):
                    blocked_pos = (x + dx, row)
                    if self.grid.get(blocked_pos) not in ['S', 'B']:
                        blocked_pos_list.add(blocked_pos)
                        self.grid[blocked_pos] = "#"

        if self.filename == "test_input.txt":
            self.print_grid()

        return len(blocked_pos_list)

    @timer(part=2)
    def solve_part_2(self, limit=4000000):
        """Solution for part 2"""
        if self.filename == "test_input.txt":
            limit = 20

        for (x, y), beacon in self.data.items():
            if ((0 <= (y - beacon['distance']) <= limit)
                    and (0 <= (y + beacon['distance']) <= limit)
                    and (0 <= (x - beacon['distance']) <= limit)
                    and (0 <= (x + beacon['distance']) <= limit)):
                yy = list(range(y - beacon['distance'], y + beacon['distance'] + 1))
                xx = beacon['distance'] - abs(yy[yy.index(row)] - y)
                for dx in range(-xx, xx + 1):
                    pass
        return None
