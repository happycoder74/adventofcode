import sys
import numpy as np
from common import timer, get_input

##################################################################
# Messy solution since it is a merge between two different files #
# Need to look into this in the future                           #
##################################################################


class Board:
    def __init__(self, board, index):
        self.board = []
        self.index = index
        self.hits = 0
        for row in board:
            row = [int(val) for val in row]
            self.board.append(row)
        self.np_board = np.array(self.board)

    def check_board(self, number, part):
        bingo = False
        if part == 1:
            for index, row in enumerate(self.board):
                if number in row:
                    i = self.board[index].index(number)
                    self.board[index][i] = -1
                    self.hits += 1
            for row in self.board:
                rowsum = sum(row)
                if rowsum == -5:
                    bingo = True
                    break
            for col in range(0, 5):
                colsum = 0
                for row in self.board:
                    colsum += row[col]
                if colsum == -5:
                    bingo = True
                    break
            return bingo
        if part == 2:
            if int(number) in self.np_board:
                self.hits += 1
                np.place(self.np_board, self.np_board == int(number), -1)
            rowsum = self.np_board.sum(axis=1)
            colsum = self.np_board.sum(axis=0)
            if (-5 in rowsum) | (-5 in colsum):
                bingo = True
                return bingo
        return None

    def sum_board(self, part):
        if part == 1:
            return sum([sum(row) for row in self.board]) + self.hits
        if part == 2:
            return self.np_board.sum() + self.hits


def check_boards(number, boards, part):
    if part == 1:
        "return true if Winner is found"
        for index, board in enumerate(boards):
            if board.check_board(int(number), part):
                return board
        return False
    if part == 2:
        winner = None
        for board in boards.copy():
            if board.check_board(int(number), part):
                winner = boards.pop(boards.index(board))
        return winner
    return None


def clean_input(data):
    numbers = data[0]
    data = data[2:]
    data = [data[i:i + 5] for i in range(0, len(data), 6)]
    data = [[d.split() for d in board] for board in data]

    boards = [Board(board, index) for index, board in enumerate(data)]
    return (numbers, boards)


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    numbers = data[0]
    boards = data[1]

    for number in numbers.split(','):
        board = check_boards(number, boards, part=1)
        if(board):
            break

    return board.sum_board(part=1) * int(number)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    numbers = data[0]
    boards = data[1]

    for number in numbers.split(","):
        winner = check_boards(number, boards, part=2)
        if len(boards) == 0:
            break

    return winner.sum_board(part=2) * int(number)


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 4))
    part1 = solve_part_1(data)

    # Some procedure in part 1 modifies the input data.
    # Need to look into this in the future.
    data = clean_input(get_input(filename, 2021, 4))
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
