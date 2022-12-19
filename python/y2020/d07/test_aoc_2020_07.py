import unittest
from aoc_2020_07 import Day07 as Day


class Test_2020_07(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(4, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(32, self.day.solve_part_2())
