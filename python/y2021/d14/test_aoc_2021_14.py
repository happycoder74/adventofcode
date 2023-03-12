import unittest
from aoc_2021_14 import Day14 as Day


class Test_2021_14(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        answer = "NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB"
        self.assertEqual(1588, self.day.solve_part_1())
        self.assertEqual(answer, self.day.solve_part_1(4))

    def test_part_2(self):
        self.assertEqual(1588, self.day.solve_part_2(10))
        self.assertEqual(2188189693529, self.day.solve_part_2())
