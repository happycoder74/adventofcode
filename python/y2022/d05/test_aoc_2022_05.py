import unittest
from aoc_2022_05 import Day05 as Day


class Test_2022_05(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual("CMZ", self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual("MCD", self.day.solve_part_2())
