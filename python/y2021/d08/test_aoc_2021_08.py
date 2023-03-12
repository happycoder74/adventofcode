import unittest
from aoc_2021_08 import Day08 as Day


class Test_2021_08(unittest.TestCase):
    def setUp(self):
        self.day = Day(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(26, self.day.solve_part_1())

    def test_part_2(self):
        data = [" ".join(
            [
                "acedgfb cdfbe gcdfa fbcad dab cefabd",
                "cdfgeb eafb cagedb ab",
                "|",
                "cdfeb fcadb cdfeb cdbaf",
            ]
        )]
        self.assertEqual(5353, Day(data=data).solve_part_2())

    def test_part_2_2(self):
        self.assertEqual(61229, self.day.solve_part_2())
