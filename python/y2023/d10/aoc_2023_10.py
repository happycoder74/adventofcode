from common import Puzzle, timer


class Day10(Puzzle, year=2023, day=10):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.directions = dict()
        self.directions["-"] = {(1, 0): (1, 0), (-1, 0): (-1, 0)}
        self.directions["|"] = {(0, 1): (0, 1), (0, -1): (0, -1)}
        self.directions["F"] = {(0, -1): (1, 0), (-1, 0): (0, 1)}
        self.directions["L"] = {(-1, 0): (0, -1), (0, 1): (1, 0)}
        self.directions["J"] = {(1, 0): (0, -1), (0, 1): (-1, 0)}
        self.directions["7"] = {(1, 0): (0, 1), (0, -1): (-1, 0)}
        max_r, max_c = (
            max(v[1] for v in self.data.keys()) + 1,
            max(v[0] for v in self.data.keys()) + 1,
        )
        self.max_r = max_r
        self.max_c = max_c
        self.deltas = {
            (1, 0): ["-", "J", "7"],
            (0, 1): ["|", "J", "L"],
            (-1, 0): ["-", "F", "L"],
            (0, -1): ["|", "F", "7"],
        }
        self.visited = list()
        self.outside = set()
        self.inside = dict()
        self.loop = set()
        self.start_pos = {
            (-1, -1): "7",
            (-1, 1): "F",
            (1, -1): "J",
            (1, 1): "L",
            (2, 0): "-",
            (-2, 0): "-",
            (0, -2): "|",
            (0, 2): "|",
        }

    @staticmethod
    def clean_input(data):
        return {(c, r): data[r][c] for r in range(0, len(data)) for c in range(0, len(data[0]))}

    def find_start(self):
        return next(k for k, v in self.data.items() if v == "S")

    def get_neighbours(self, point):
        return {
            (point[0] + d[0], point[1] + d[1]): p
            for d, p in self.deltas.items()
            if (0 <= point[0] + d[0] < self.max_c) and (0 <= point[1] + d[1] < self.max_r)
        }

    @timer(part=1)
    def solve_part_1(self):
        self.start = self.find_start()
        pos = self.start
        neighbours = self.get_neighbours(self.start)
        p0, p1 = [p for p, v in neighbours.items() if self.data[p] in v]
        self.data[self.start] = self.start_pos[(p1[0] - p0[0], p1[1] - p0[1])]
        match self.data[self.start]:
            case "|" | "F" | "7":
                direction = (0, 1)
            case "-" | "L":
                direction = (1, 0)
            case "J" | _:
                direction = (0, 1)

        self.visited.append((self.start, direction))
        while True:
            pos = pos[0] + direction[0], pos[1] + direction[1]
            self.loop.add(pos)
            if pos == self.start:
                return len(self.loop) // 2
            self.visited.append((pos, direction))
            match self.data[pos]:
                case "|" | "-":
                    continue
                case "L" | "7":
                    direction = direction[1], direction[0]
                    self.visited.append((pos, direction))
                case "J" | "F":
                    direction = -direction[1], -direction[0]
                    self.visited.append((pos, direction))
                case _:
                    print("Should not be here...")
                    raise IndexError("Error in grid index")

    def find_inside(self, point, color):
        fill = {point}
        while fill:
            p = fill.pop()
            if p not in self.data:
                continue
            if (p in self.inside) or (p in self.loop):
                continue
            self.inside[p] = color
            for nb in ((p[0] + d[0], p[1] + d[1]) for d in self.deltas):
                fill.add(nb)

    @timer(part=2)
    def solve_part_2(self):
        for pos, direction in self.visited:
            direction_1 = pos[0] + direction[1], pos[1] - direction[0]
            direction_2 = pos[0] - direction[1], pos[1] + direction[0]
            self.find_inside(direction_1, "a")
            self.find_inside(direction_2, "b")

        self.outside = {self.inside.get((c, 0)) for c in range(self.max_c)}
        self.outside = self.outside.union(
            {self.inside.get((c, self.max_r - 1)) for c in range(self.max_c)}
        )
        # self.print_domain()
        if "a" in self.outside:
            return sum(v == "b" for v in self.inside.values())
        else:
            return sum(v == "a" for v in self.inside.values())

    def print_domain(self):
        ttable = {
            "-": "\u2500",
            "|": "\u2502",
            "L": "\u2514",
            "J": "\u2518",
            "F": "\u250C",
            "7": "\u2510",
        }

        for r in range(0, self.max_r):
            print(f"{r:03d}: ", end="")
            for c in range(0, self.max_c):
                if (c, r) in self.loop:
                    print(ttable.get(self.data[(c, r)], self.data[(c, r)]), end="")
                elif (c, r) in self.inside:
                    print(self.inside[(c, r)], end="")
                elif (c, r) in self.outside:
                    print("O", end="")
                else:
                    print(".", end="")
            print("\n", end="")
