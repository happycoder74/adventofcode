import unittest
from aoc_2020_04 import Day4


class Test_2020_04(unittest.TestCase):
    def setUp(self):
        self.filename = [
            "test_input.txt",
            "test_input_invalid.txt",
            "test_input_valid.txt"
        ]

    def test_part_1(self):
        self.assertEqual(2, Day4(filename=self.filename[0]).solve_part_1())

    def test_part_2(self):
        self.assertEqual(0, Day4(filename=self.filename[1]).solve_part_2())

    def test_part_3(self):
        self.assertEqual(4, Day4(filename=self.filename[2]).solve_part_2())
