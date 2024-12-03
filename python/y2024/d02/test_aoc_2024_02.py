import unittest

from aoc_2024_02 import Day02


class Test_2024_02(unittest.TestCase):
    def setUp(self):
        self.day = Day02(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(2, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(4, self.day.solve_part_2())
