import unittest
from aoc_2022_03 import Day03 as Day


class Test_2022_03(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(157, Day(filename="test_input.txt").solve_part_1())

    def test_part_2(self):
        self.assertEqual(70, Day(filename="test_input.txt").solve_part_2())
