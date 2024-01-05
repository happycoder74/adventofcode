class Grid(object):
    def __init__(self, data):
        self.grid = dict()
        self.max_c = len(data[0])
        self.max_r = len(data)
        for c in range(self.max_c):
            for r in range(self.max_r):
                self.grid[(r, c)] = data[r][c]

    def get_column(self, col) -> list[str]:
        return [self.grid[row, col] for row in range(self.max_r)]

    def get_row(self, row) -> list[str]:
        return [self.grid[row, col] for col in range(self.max_c)]
