import unittest
from aoc_2022_25 import Day25


class Test_2022_25(unittest.TestCase):
    def setUp(self):
        self.day = Day25(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual("2=-1=0", self.day.solve_part_1())
