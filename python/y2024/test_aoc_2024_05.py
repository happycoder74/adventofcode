import unittest

from aoc_2024_05 import Day05


class Test_2024_05(unittest.TestCase):
    def setUp(self):
        self.day = Day05(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(143, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(0, self.day.solve_part_2())
