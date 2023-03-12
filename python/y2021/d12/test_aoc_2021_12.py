import unittest
from aoc_2021_12 import Day12 as Day


class Test_2021_12(unittest.TestCase):
    def setUp(self):
        self.data = [
            "start-A",
            "start-b",
            "A-c",
            "A-b",
            "b-d",
            "A-end",
            "b-end"
        ]

    def test_part_1(self):
        self.assertEqual(10, Day(data=self.data).solve_part_1())

    def test_part_2(self):
        self.assertEqual(36, Day(data=self.data).solve_part_2())
