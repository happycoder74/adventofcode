import unittest

from aoc_2023_07 import Day07


class Test_2023_07(unittest.TestCase):
    def setUp(self):
        self.day = Day07(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(6440, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(5905, self.day.solve_part_2())
