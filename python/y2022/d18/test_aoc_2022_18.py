import unittest
from aoc_2022_18 import Day18


class Test_2022_18(unittest.TestCase):
    def setUp(self):
        self.data = [
            ["1,1,1",
             "2,1,1"],
            ["1,1,1",
             "3,3,3"]
        ]

    def test_part_1_simple(self):
        self.assertEqual(10, Day18(data=self.data[0]).solve_part_1())
        self.assertEqual(12, Day18(data=self.data[1]).solve_part_1())

    def test_part_1(self):
        self.assertEqual(64, Day18(filename="test_input.txt").solve_part_1())

    def test_part_2(self):
        self.assertEqual(58, Day18(filename="test_input.txt").solve_part_2())
