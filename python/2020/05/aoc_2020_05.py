import sys
from common import timer, Puzzle


class Day5(Puzzle, year=2020, day=5):
    @staticmethod
    def clean_input(data):
        return data

    def find_row(self, data):
        first_row = 0
        last_row = 127
        for letter in data[:-1]:
            if letter == "F":
                last_row = (last_row - first_row + 1) / 2 + first_row - 1
            else:
                first_row = (last_row - first_row + 1) / 2 + first_row
        if (data[-1] == "F"):
            return first_row
        else:
            return last_row

    def find_seat(self, data):
        first = 0
        last = 7
        for letter in data[:-1]:
            if letter == "L":
                last = (last - first + 1) / 2 + first - 1
            else:
                first = (last - first + 1) / 2 + first
        if (data[-1] == "L"):
            return first
        else:
            return last

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        max_id = 0
        for row in self.data:
            seat_id = (self.find_row(row[0:7]) * 8 +
                       self.find_seat(row[7:]))
            if seat_id >= max_id:
                max_id = seat_id
        return max_id

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        seat_id_list = []
        for row in self.data:
            seat_id = (self.find_row(row[0:7]) * 8 +
                       self.find_seat(row[7:]))
            seat_id_list.append(int(seat_id))
        seat_id_list.sort()
        for index, seat in enumerate(seat_id_list[:-1]):
            if seat_id_list[index + 1] != seat + 1:
                return seat + 1
        return None


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day5(filename=filename).solve_all()
