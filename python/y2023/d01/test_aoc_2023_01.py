import unittest
from aoc_2023_01 import Day01


class Test_2023_01(unittest.TestCase):
    def setUp(self):
        self.day = Day01(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(142, self.day.solve_part_1())

    def test_part_2(self):
        inputdata = """
two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen
        """
        self.data = inputdata.splitlines()
        self.assertEqual(281, Day01(data=self.data).solve_part_2())
