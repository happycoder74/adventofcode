import unittest
from aoc_2022_21 import Day21


class Test_2022_21(unittest.TestCase):
    def setUp(self):
        self.day = Day21(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(152, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(301, self.day.solve_part_2())
