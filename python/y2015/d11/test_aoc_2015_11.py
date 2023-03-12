import unittest
from aoc_2015_11 import Day11


class Test_2015_11(unittest.TestCase):
    def test_part_1(self):
        self.data = ["ghijklmn"]
        self.assertEqual("ghjaabcc", Day11(data=self.data).solve_part_1())

    def test_part_1b(self):
        self.data = ["abcdefgh"]
        self.assertEqual("abcdffaa", Day11(data=self.data).solve_part_1())
