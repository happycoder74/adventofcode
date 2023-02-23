import unittest
from aoc_2021_06 import Day06 as Day


class Test_2021_06(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(5934, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(26984457539, self.day.solve_part_2())
