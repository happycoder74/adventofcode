import unittest

from aoc_2023_11 import Day11


class Test_2023_11(unittest.TestCase):
    def setUp(self):
        self.day = Day11(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(374, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(1030, self.day.solver(multiplier=10))

    def test_part_2b(self):
        self.assertEqual(8410, self.day.solver(multiplier=100))
