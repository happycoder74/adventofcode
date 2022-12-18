import unittest
from aoc_2020_01 import Day01


class Test_2020_01(unittest.TestCase):
    def test_part_1(self):
        self.assertEqual(514579,
                         Day01(filename="test_input.txt").solve_part_1())

    def test_part_2(self):
        self.assertEqual(241861950,
                         Day01(filename="test_input.txt").solve_part_2())
