import unittest
from aoc_2022_13 import Day13


class Test_2022_13(unittest.TestCase):
    def setUp(self):
        self.day = Day13(filename="test_input.txt")

    def test_solve_part_1(self):
        self.assertEqual(13, self.day.solve_part_1())

    def test_solve_part_2(self):
        self.assertEqual(140, self.day.solve_part_2())
