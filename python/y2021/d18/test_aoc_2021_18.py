import unittest
from aoc_2021_18 import Day18, SnailfishNumber


class Test_2021_18(unittest.TestCase):
    def setUp(self):
        self.testdata = [
            "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
            "[[[5,[2,8]],4],[5,[[9,9],0]]]",
            "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
            "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
            "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
            "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
            "[[[[5,4],[7,7]],8],[[8,3],8]]",
            "[[9,3],[[9,9],[6,[4,9]]]]",
            "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
            "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]",
        ]
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
        number = SnailfishNumber(
            "[[[[4,3],4],4],[7,[[8,4],9]]]"
        ) + SnailfishNumber("[1,1]")

        answer = "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"
        self.assertEqual(answer, SnailfishNumber.to_string(number))

    def test_part_1(self):
        self.assertEqual(4140, Day18(data=self.testdata).solve_part_1())

    def test_part_2(self):
        self.assertEqual(3993, Day18(data=self.testdata).solve_part_2())
