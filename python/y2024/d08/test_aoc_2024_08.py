import unittest

from aoc_2024_08 import Day08


class Test_2024_08(unittest.TestCase):
    def setUp(self):
        self.day = Day08(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(14, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(34, self.day.solve_part_2())
