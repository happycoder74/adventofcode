from common import Grid, Puzzle, timer


class Day13(Puzzle, year=2023, day=13):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)

    @staticmethod
    def clean_input(data):
        groups = Puzzle.parse_input_groups(data)
        return [Grid(d) for d in groups]

    @timer(part=1)
    def solve_part_1(self) -> int:
        sum_rows = 0
        sum_cols = 0

        for grid in self.data:
            # Check mirror cols
            for checkcol in range(1, grid.max_c):
                colrange = range(0, checkcol)
                colcheck = True
                for c1, c2 in zip(
                    colrange[::-1], [checkcol + i for i in colrange if checkcol + i < grid.max_c]
                ):
                    column0 = grid.get_column(c1)
                    column1 = grid.get_column(c2)
                    if column0 != column1:
                        colcheck = False
                        break
                if colcheck:
                    sum_cols += checkcol

            # Check mirror rows
            for checkrow in range(1, grid.max_r):
                rowrange = range(0, checkrow)
                rowcheck = True
                for r1, r2 in zip(
                    rowrange[::-1], [checkrow + i for i in rowrange if checkrow + i < grid.max_r]
                ):
                    row0 = grid.get_row(r1)
                    row1 = grid.get_row(r2)
                    if row0 != row1:
                        rowcheck = False
                        break
                if rowcheck:
                    sum_rows += checkrow

        return sum_cols + 100 * sum_rows

    @timer(part=2)
    def solve_part_2(self) -> str | int:
        return "NOT IMPLEMENTED"
