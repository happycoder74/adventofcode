import unittest
from aoc_2022_15 import Day15


class Test_2022_15(unittest.TestCase):
    def setUp(self):
        self.day = Day15(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(26, self.day.solve_part_1(row=10))

    def test_part_2(self):
        self.assertEqual(None, self.day.solve_part_2())
