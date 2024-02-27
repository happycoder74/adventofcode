from common import Grid, Puzzle, timer


class Day13(Puzzle, year=2023, day=13):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.candidates = []

    @staticmethod
    def clean_input(data):
        groups = Puzzle.parse_input_groups(data)
        return [Grid(d) for d in groups]

    def find_mirror(self, grid, kind="row") -> int:
        mirror = 0
        limit = grid.max_r if kind == "row" else grid.max_c
        for check in range(1, limit):
            mirrors = []
            check_range = range(0, check)
            for c1, c2 in zip(
                check_range[::-1], [check + i for i in check_range if check + i < limit]
            ):
                item0 = set(grid.get_tuple(c1, kind=kind))
                item1 = set(grid.get_tuple(c2, kind=kind))

                diffset = item0.symmetric_difference(item1)
                mirrors.append((len(diffset) == 0, len(diffset)))

            mirror_check = [i for i in mirrors if not i[0]]
            if len(mirror_check) == 0:
                mirror = check
            elif len(mirror_check) == 1:
                if mirror_check[0][1] == 2:
                    self.candidates.append((kind, check))

        return mirror

    @timer(part=1)
    def solve_part_1(self) -> int:
        sum_rows = 0
        sum_cols = 0

        for grid in self.data:
            # Check mirror cols
            mirror_column = self.find_mirror(grid, kind="column")
            sum_cols += mirror_column

            # Check mirror rows
            mirror_row = self.find_mirror(grid, kind="row")
            sum_rows += mirror_row

        return sum_cols + 100 * sum_rows

    @timer(part=2)
    def solve_part_2(self) -> str | int:
        sum_cols = sum([c[1] for c in self.candidates if c[0] == "column"])
        sum_rows = sum([c[1] for c in self.candidates if c[0] == "row"])
        return sum_cols + 100 * sum_rows
