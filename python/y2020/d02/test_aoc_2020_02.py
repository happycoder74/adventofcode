import unittest
from aoc_2020_02 import Day02 as Day


class Test_2020_02(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(2, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(1, self.day.solve_part_2())
