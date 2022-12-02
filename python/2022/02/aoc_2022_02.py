import sys
from common import timer, Puzzle


class Day2(Puzzle, year=2022, day=2):
    @staticmethod
    def clean_input(data):
        draws = list()
        for row in data:
            draws.append(row.split())
        return draws

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        shape_points = {'X': 1, 'Y': 2, 'Z': 3}
        col = ''.join(shape_points.keys())
        row = "ABC"
        p = [[3, 6, 0], [0, 3, 6], [6, 0, 3]]

        return sum([p[row.index(d[0])][col.index(d[1])] + shape_points[d[1]]
                    for d in self.data])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        shape_points = {'X': 1, 'Y': 2, 'Z': 3}
        col = ''.join(shape_points.keys())
        req_shape = {"['A', 'X']": 'Z',
                     "['A', 'Y']": 'X',
                     "['A', 'Z']": 'Y',
                     "['B', 'X']": 'X',
                     "['B', 'Y']": 'Y',
                     "['B', 'Z']": 'Z',
                     "['C', 'X']": 'Y',
                     "['C', 'Y']": 'Z',
                     "['C', 'Z']": 'X'
                     }
        p = [0, 3, 6]
        points = 0
        for d in self.data:
            points += p[col.index(d[1])] + shape_points[req_shape[str(d)]]
        return points


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day2(filename=filename).solve_all()
