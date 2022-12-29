import unittest
from aoc_2022_20 import Day20


class Test_2022_20(unittest.TestCase):
    def setUp(self):
        self.day = Day20(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(3, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(1623178306, self.day.solve_part_2())
