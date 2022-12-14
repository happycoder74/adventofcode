import sys
from common import timer, Puzzle


class Day05(Puzzle, year=2020, day=5):
    @staticmethod
    def clean_input(data):
        return sorted([Day05.find_id(row) for row in data])

    @staticmethod
    def find_id(data: str):
        seat_id = data.translate(str.maketrans('FBLR', '0101'))
        return int(seat_id, 2)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.data[-1]

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        seats = self.data
        all_seats = set(range(seats[0], seats[-1] + 1))
        return all_seats.difference(seats).pop()


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day05(filename=filename).solve_all()
