import unittest
from aoc_2022_03 import Day3


class Test_2022_03(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(157, Day3(filename="test_input.txt").solve_part_1())

    def test_part_2(self):
        self.assertEqual(70, Day3(filename="test_input.txt").solve_part_2())
