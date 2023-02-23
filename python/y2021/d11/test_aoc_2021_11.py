import unittest
from aoc_2021_11 import Day11 as Day


class Test_2021_11(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(204, self.day.solve_part_1(10))

    def test_part_1_100(self):
        self.assertEqual(1656, self.day.solve_part_1(100))

    def test_part_2(self):
        self.assertEqual(195, self.day.solve_part_2())
