import unittest
from aoc_2015_01 import Day1


class Test_2015_01(unittest.TestCase):
    def setUp(self):
        self.day = Day1(filename="input.txt")

    def test_part_1(self):
        self.day.data = ')())())'
        self.assertEqual(-3, self.data.solve_part_1())

    def test_part_2(self):
        self.data.data = '()())'
        self.assertEqual(5, self.data.solve_part_2())
