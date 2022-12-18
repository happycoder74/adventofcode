import unittest
from aoc_2022_07 import Day07 as Day


class Test_2022_07(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(95437, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(24933642, self.day.solve_part_2())
