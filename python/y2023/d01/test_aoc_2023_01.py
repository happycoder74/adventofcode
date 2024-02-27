import os
import unittest

from aoc_2023_01 import Day01


class Test_2023_01(unittest.TestCase):
    def setUp(self):
        self.day = Day01(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(142, self.day.solve_part_1())

    def test_part_2(self):
        self.day = Day01(
            filename="c:/home/yy11510/projects/adventofcode/data/2023/01/test_input_2.txt"
        )
        self.assertEqual(281, self.day.solve_part_2())
