import unittest
from aoc_2021_17 import Day17 as Day


class Test_2021_17(unittest.TestCase):
    def setUp(self):
        data = ['target area: x=20..30, y=-10..-5']
        self.day = Day(data=data)

    def test_part_1(self):
        self.assertEqual(45, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(112, self.day.solve_part_2())
