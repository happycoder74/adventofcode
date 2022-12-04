import unittest
from aoc_2022_04 import Day4


class Test_2022_04(unittest.TestCase):
    def setUp(self):
        self.data = [
            "2-4,6-8",
            "3-3,4-5",
            "5-7,7-9",
            "2-8,3-7",
            "6-6,4-6",
            "2-6,4-8"
        ]

    def test_part_1(self):
        self.assertEqual(2,
                         Day4(year=2022, day=4, data=self.data).solve_part_1())

    def test_part_2(self):
        self.assertEqual(4,
                         Day4(year=2022, day=4, data=self.data).solve_part_2())
