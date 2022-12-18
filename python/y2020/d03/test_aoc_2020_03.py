import unittest
from aoc_2020_03 import Day03 as Day


class Test_2020_03(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(7, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(336, self.day.solve_part_2())
