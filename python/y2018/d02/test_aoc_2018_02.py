import unittest
from aoc_2018_02 import Day02


class Test_2018_02(unittest.TestCase):
    def test_part_1(self):
        self.data = [
            "abcdef",
            "bababc",
            "abbcde",
            "abcccd",
            "aabcdd",
            "abcdee",
            "ababab",
        ]
        self.assertEqual(12, Day02(data=self.data).solve_part_1())

    def test_part_2(self):
        self.data = [
            "abcde",
            "fghij",
            "klmno",
            "pqrst",
            "fguij",
            "axcye",
            "wvxyz",
        ]
        self.assertEqual("fgij", Day02(data=self.data).solve_part_2())
