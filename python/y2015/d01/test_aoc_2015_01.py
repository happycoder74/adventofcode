import unittest
from aoc_2015_01 import Day01


class Test_2015_01(unittest.TestCase):
    def setUp(self):
        pass

    def test_part_1(self):
        self.day = Day01(data=[')())())'])
        self.assertEqual(-3, self.day.solve_part_1())

    def test_part_2(self):
        self.day = Day01(data=['()())'])
        self.assertEqual(5, self.day.solve_part_2())
