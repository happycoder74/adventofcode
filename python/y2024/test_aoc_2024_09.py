import unittest

from aoc_2024_09 import Day09


class Test_2024_09(unittest.TestCase):
    def setUp(self):
        self.day = Day09(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(1928, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(2858, self.day.solve_part_2())
