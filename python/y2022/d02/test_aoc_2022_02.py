import unittest
from aoc_2022_02 import Day02 as Day


class Test_2022_02(unittest.TestCase):
    def setUp(self):
        self.data = [
            "A Y",
            "B X",
            "C Z"
        ]

    def test_part_1(self):
        self.assertEqual(15, Day(data=self.data).solve_part_1())

    def test_part_2(self):
        self.assertEqual(12, Day(data=self.data).solve_part_2())
