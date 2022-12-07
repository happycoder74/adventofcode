import unittest
from aoc_2020_05 import Day5


class Test_2020_05(unittest.TestCase):
    def setUp(self):
        data = [
            "BFFFBBFRRR",
            "FFFBBBFRRR",
            "BBFFBBFRLL",
            "FBFBBFFRLR"
        ]
        self.day = Day5(data=data)

    def test_part_1(self):
        self.assertEqual(820, self.day.solve_part_1())


