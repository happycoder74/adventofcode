import os
import unittest
from aoc_2020_04 import Day04 as Day


class Test_2020_04(unittest.TestCase):
    def setUp(self):
        self.filename = [
            "test_input.txt",
            "../data/2020/04/test_input_invalid.txt",
            "../data/2020/04/test_input_valid.txt",
        ]

    def test_part_1(self):
        self.assertEqual(2, Day(filename=self.filename[0]).solve_part_1())

    def test_part_2(self):
        self.assertEqual(0, Day(filename=self.filename[1]).solve_part_2())

    def test_part_3(self):
        self.assertEqual(4, Day(filename=self.filename[2]).solve_part_2())
