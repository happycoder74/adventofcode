import unittest
from aoc_2021_02 import Day02 as Day


class Test_2021_02(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(150, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(900, self.day.solve_part_2())
