import unittest
from aoc_2021_05 import Day05 as Day


class Test_2021_05(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(5, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(12, self.day.solve_part_2())
