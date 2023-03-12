from common import timer, Puzzle


class Day13(Puzzle, year=2021, day=13):
    @staticmethod
    def clean_input(data: list):
        return Puzzle.parse_input_groups(data)

    def create_paper(self) -> None:
        xmax: str = 0
        ymax: str = 0
        dots: list

        dots = self.data[0]
        dots = [tuple(list(map(int, d.split(",")))) for d in dots]

        for dot in dots:
            xmax = dot[0] if dot[0] > xmax else xmax
            ymax = dot[1] if dot[1] > ymax else ymax

        self.paper = [[0 for i in range(xmax + 1)] for j in range(ymax + 1)]

        for dot in dots:
            xc = dot[0]
            yc = dot[1]
            self.paper[yc][xc] = 1

    def fold_paper(self, direction: str, position: int) -> list:
        folded: list
        if direction == "y":
            folded = [
                [0 for _ in range(len(self.paper[0]))] for _ in range(position)
            ]
            for j in range(0, min(position, (len(self.paper) - position - 1))):
                for i in range(len(self.paper[0])):
                    folded[len(folded) - 1 - j][i] = (
                        self.paper[position + j + 1][i]
                        + self.paper[position - j - 1][i]
                    )
        elif direction == "x":
            folded = [
                [0 for _ in range(position)] for _ in range(len(self.paper))
            ]
            for j in range(len(self.paper)):
                for i in range(
                    0, min(position, (len(self.paper[0]) - position - 1))
                ):
                    folded[j][len(folded[0]) - 1 - i] = (
                        self.paper[j][position + i + 1]
                        + self.paper[j][position - i - 1]
                    )

        return folded

    def print_paper(self):
        p = self.paper.copy()

        for j, row in enumerate(self.paper):
            for i, col in enumerate(row):
                if col == 0:
                    p[j][i] = "."
                else:
                    p[j][i] = "#"
            p[j] = ["".join(p[j])]

        for row in p:
            print(row[0].replace(".", " "))

    def solution(self, loops=1):

        self.folds = [
            (f.split("=")[0][-1], int(f.split("=")[1])) for f in self.data[1]
        ]

        self.create_paper()

        for fold_index, fold in enumerate(self.folds):
            if loops == 1 and fold_index >= loops:
                break
            self.paper = self.fold_paper(fold[0], fold[1])

        num = 0
        for row in self.paper:
            for col in row:
                if col > 0:
                    num += 1

        if loops != 1:
            self.print_paper()
        return num

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.solution(loops=1)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.solution(loops=len(self.folds))
