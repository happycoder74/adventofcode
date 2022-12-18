import unittest
from aoc_2022_12 import Day12


class Test_2022_12(unittest.TestCase):
    def setUp(self):
        self.day = Day12(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(31, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(29, self.day.solve_part_2())
