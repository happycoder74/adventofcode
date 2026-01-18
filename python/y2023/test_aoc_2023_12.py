import unittest

from aoc_2023_12 import Day12


class Test_2023_12(unittest.TestCase):
    def setUp(self):
        self.day = Day12(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(21, self.day.solve_part_1())

    # def test_part_2(self):
    #     self.assertEqual(0, self.day.solve_part_2())
