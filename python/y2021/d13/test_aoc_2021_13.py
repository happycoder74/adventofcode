import unittest
from aoc_2021_13 import Day13


class Test_2021_13(unittest.TestCase):
    def setUp(self):
        self.day = Day13(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(None, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(None, self.day.solve_part_2())
