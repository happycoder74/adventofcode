import copy
import numpy as np
from common import timer, Puzzle

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


def check_boards_part_1(number, boards):
    "return true if Winner is found"
    for board in boards:
        if board.check_board(int(number), 1):
            return board
    return False


def check_boards_part_2(number, boards):
    winner = None
    for board in boards.copy():
        if board.check_board(int(number), 2):
            winner = boards.pop(boards.index(board))
    return winner


class Day04(Puzzle, year=2021, day=4):
    @staticmethod
    def clean_input(data) -> tuple[str, list[Board]]:
        numbers = data[0]
        data = data[2:]
        data = [data[i:i + 5] for i in range(0, len(data), 6)]
        data = [[d.split() for d in board] for board in data]

        boards: list[Board] = [
            Board(board, index) for index, board in enumerate(data)
        ]
        return (numbers, boards)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        numbers = self.data[0]
        boards = copy.deepcopy(self.data[1])
        board = None
        for number in numbers.split(','):
            board = check_boards_part_1(number, boards)
            if(board):
                break

        if board:
            return board.sum_board(part=1) * int(number)
        return None

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        numbers = self.data[0]
        boards = self.data[1]

        for number in numbers.split(","):
            winner = check_boards_part_2(number, boards)
            if len(boards) == 0:
                break

        return winner.sum_board(part=2) * int(number)
