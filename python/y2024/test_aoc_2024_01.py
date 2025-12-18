import os
import unittest

from aoc_2024_01 import Day01


class Test_2024_01(unittest.TestCase):
    def setUp(self):
        self.day = Day01(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(11, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(31, self.day.solve_part_2())
