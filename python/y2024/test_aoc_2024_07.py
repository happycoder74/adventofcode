import unittest

from aoc_2024_07 import Day07


class Test_2024_07(unittest.TestCase):
    def setUp(self):
        self.day = Day07(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(3749, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(11387, self.day.solve_part_2())
