import unittest
from aoc_2021_07 import Day07 as Day


class Test_2021_07(unittest.TestCase):
    def setUp(self):
        self.day = Day(data=["16,1,2,0,4,2,7,1,2,14"])

    def test_part_1(self):
        self.assertEqual(37, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(168, self.day.solve_part_2())
