import unittest
from aoc_2022_11 import Day11


class Test_2022_11(unittest.TestCase):
    def setUp(self):
        self.day = Day11(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(None, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(None, self.day.solve_part_2())
