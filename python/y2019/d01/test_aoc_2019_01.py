import unittest
from aoc_2019_01 import Day01 as Day


class Test_2019_01(unittest.TestCase):
    def setUp(self):
        self.data = [
            "100756"
        ]

    def test_part_1(self):
        self.assertEqual(33583, Day(data=self.data).solve_part_1())

    def test_part_2(self):
        self.assertEqual(50346, Day(data=self.data).solve_part_2())
