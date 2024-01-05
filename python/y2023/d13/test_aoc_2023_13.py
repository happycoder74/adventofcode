import unittest

from aoc_2023_13 import Day13


class Test_2023_13(unittest.TestCase):
    def setUp(self):
        self.day = Day13(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(405, self.day.solve_part_1())

    # def test_part_2(self):
    #     self.assertEqual(0, self.day.solve_part_2())
