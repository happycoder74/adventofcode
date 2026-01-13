import unittest

from aoc_2024_10 import Day10


class Test_2024_10(unittest.TestCase):
    def setUp(self):
        self.day = Day10(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(36, self.day.solve_part_1())

    def test_part_2(self):
        _ = self.day.solve_part_1()
        self.assertEqual(81, self.day.solve_part_2())
