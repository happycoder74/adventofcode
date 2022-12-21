import unittest
from aoc_2022_14 import Day14


class Test_2022_14(unittest.TestCase):
    def setUp(self):
        self.day = Day14(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(None, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(None, self.day.solve_part_2())
