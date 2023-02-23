import unittest
from aoc_2021_09 import Day09 as Day


class Test_2021_09(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(15, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(1134, self.day.solve_part_2())
