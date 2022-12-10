import unittest
from aoc_2022_10 import Day10


class Test_2022_10(unittest.TestCase):
    def setUp(self):
        self.day = Day10(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(13140, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(None, self.day.solve_part_2())
