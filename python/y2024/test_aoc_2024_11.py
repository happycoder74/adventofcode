import unittest

from aoc_2024_11 import Day11


class Test_2024_11(unittest.TestCase):
    def setUp(self):
        self.day = Day11(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(22, self.day.solve_part_1(iterations=6))

    def test_part_1_2(self):
        self.assertEqual(55312, self.day.solve_part_1(iterations=25))

    def test_part_2(self):
        self.assertEqual(0, self.day.solve_part_2())
