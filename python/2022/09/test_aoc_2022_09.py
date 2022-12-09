import unittest
from aoc_2022_09 import Day9


class Test_2022_09(unittest.TestCase):
    def setUp(self):
        self.day = Day9(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(13, self.day.solve_part_1())

    def test_part_2(self):
        self.day2 = Day9(filename="test_input_2.txt")
        self.assertEqual(36, self.day.solve_part_2())
