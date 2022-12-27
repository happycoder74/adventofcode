import re
from common import timer, Puzzle


def combine_ranges(ranges):
    print(ranges)
    updated_ranges = list()
    non_matching_ranges = list()
    p_start, p_end = ranges[0]
    for r_start, r_end in ranges[1:]:
        if r_start <= p_end and p_start <= r_end:
            updated_ranges.append((min(r_start, p_start), max(r_end, p_end)))
        else:
            non_matching_ranges.append((r_start, r_end))
    if updated_ranges:
        return combine_ranges(updated_ranges + non_matching_ranges)
    elif non_matching_ranges:
        return [(p_start, p_end)] + combine_ranges(non_matching_ranges)
    else:
        return [(p_start, p_end)]


class Day15(Puzzle, year=2022, day=15):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.grid = dict()
        self.setup_grid()

    @staticmethod
    def clean_input(data):
        sensors = {}
        for row in data:
            x, y, xx, yy = list(
                map(int, re.findall(pattern=r"\w*=(-{0,1}\d+)", string=row))
            )
            sensors[(x, y)] = {
                "beacon": (xx, yy),
                "distance": (abs(x - xx) + abs(y - yy)),
            }

        return sensors

    def setup_grid(self):
        for pos, beacon in self.data.items():
            self.grid[pos] = "S"
            self.grid[beacon["beacon"]] = "B"

    def print_grid(self):
        limits_x = (
            min(p[0] for p in self.grid.keys()),
            max(p[0] for p in self.grid.keys()),
        )
        limits_y = (
            min(p[1] for p in self.grid.keys()),
            max(p[1] for p in self.grid.keys()),
        )
        for row in range(limits_y[0], limits_y[1] + 1):
            print(f"{row:4d}", end="")
            for col in range(limits_x[0], limits_x[1] + 1):
                if self.grid.get((col, row), " ") in ["S", "B", "#"]:
                    print(self.grid.get((col, row), " "), end="")
                else:
                    print(".", end="")
            print()

    @timer(part=1)
    def solve_part_1(self, row=2000000):
        """Solution for part 1"""
        if self.filename == "test_input.txt":
            row = 10

        ranges = set()

        for (x, y), beacon in self.data.items():
            distance = abs(y - row)
            if distance <= beacon["distance"]:
                ranges |= set(
                    range(
                        x - abs(beacon["distance"] - distance),
                        x + abs(beacon["distance"] - distance + 1),
                    )
                )

        no_pos = len(ranges)
        for beacon in {b["beacon"] for _, b in self.data.items()}:
            if beacon[1] == row:
                print(f"removing beacon: {beacon=}")
                no_pos -= 1

        return no_pos

    @timer(part=2)
    def solve_part_2(self, limit=4000000):
        """Solution for part 2"""
        return None
