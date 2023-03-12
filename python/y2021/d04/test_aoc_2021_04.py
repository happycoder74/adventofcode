import unittest
from aoc_2021_04 import Day04 as Day


class Test_2021_04(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(4512, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(1924, self.day.solve_part_2())
