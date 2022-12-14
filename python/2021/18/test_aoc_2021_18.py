import unittest
from aoc_2021_18 import Day18, SnailfishNumber


class Test_2021_18(unittest.TestCase):
    def setUp(self):
        Solver = Day18(filename="input.txt")
        self.filedata = Solver.data
        self.numbers = [
            [[1, 2], [[3, 4], 5]],
            [[[[0, 7], 4], [[7, 8], [6, 0]]], [8, 1]],
            [[[[1, 1], [2, 2]], [3, 3]], [4, 4]],
            [[[[3, 0], [5, 3]], [4, 4]], [5, 5]],
            [[[[5, 0], [7, 4]], [5, 5]], [6, 6]],
            [[[[8, 7], [7, 7]], [[8, 6], [7, 7]]], [[[0, 7], [6, 6]], [8, 7]]],
            [
                [[[6, 6], [7, 6]], [[7, 7], [7, 0]]],
                [[[7, 7], [7, 7]], [[7, 8], [9, 9]]],
            ],
        ]
        self.answers = [143, 1384, 445, 791, 1137, 3488, 4140]

    def test_magnitude(self):
        for number, answer in zip(self.numbers, self.answers):
            SN = SnailfishNumber(str(number))
            self.assertEqual(answer, SnailfishNumber.magnitude(SN))

    def test_add(self):
        number = (
            SnailfishNumber("[[[[4,3],4],4],[7,[[8,4],9]]]") +
            SnailfishNumber("[1,1]"))

        answer = "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"
        self.assertEqual(answer, SnailfishNumber.to_string(number))
