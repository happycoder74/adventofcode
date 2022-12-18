import unittest
from aoc_2022_01 import Day01 as Day


class Test_2022_01(unittest.TestCase):
    def setUp(self):
        self.filename = "test_input.txt"

    def test_part_1(self):
        self.assertEqual(24000, Day(filename=self.filename).solve_part_1())

    def test_part_2(self):
        self.assertEqual(45000, Day(filename=self.filename).solve_part_2())
