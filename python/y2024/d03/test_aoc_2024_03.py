import unittest

from aoc_2024_03 import Day03


class Test_2024_03(unittest.TestCase):
    def test_part_1(self):
        self.day = Day03(filename="test_input.txt")
        self.assertEqual(161, self.day.solve_part_1())

    def test_part_2(self):
        self.day = Day03(
            filename="/home/christian/projects/adventofcode/data/2024/03/test_input_2.txt"
        )
        self.assertEqual(48, self.day.solve_part_2())
