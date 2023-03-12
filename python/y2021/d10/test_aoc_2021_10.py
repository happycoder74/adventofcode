import unittest
from aoc_2021_10 import Day10 as Day


class Test_2021_10(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(26397, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(288957, self.day.solve_part_2())
