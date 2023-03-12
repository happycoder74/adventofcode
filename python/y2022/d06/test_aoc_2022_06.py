import unittest
from aoc_2022_06 import Day06 as Day


class Test_2022_06(unittest.TestCase):
    def setUp(self):
        self.data = [
            "mjqjpqmgbljsphdztnvjfqwrcgsmlb"
        ]

    def test_part_1(self):
        self.assertEqual(7, Day(data=self.data).solve_part_1())

    def test_part_2(self):
        self.assertEqual(19, Day(data=self.data).solve_part_2())
