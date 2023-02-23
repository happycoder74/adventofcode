import unittest
from aoc_2021_03 import Day03 as Day


class Test_2021_03(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(198, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(230, self.day.solve_part_2())
