import unittest
from aoc_2022_08 import Day08 as Day


class Test_2022_08(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(21, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(8, self.day.solve_part_2())
