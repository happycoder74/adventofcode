import os
import unittest
from pathlib import Path

from aoc_2023_08 import Day08


class Test_2023_08(unittest.TestCase):
    def setUp(self):
        filepath = os.getenv("AOC_DATA_LOCATION") or "."
        self.dataPath = Path(filepath) / Path("2023") / Path("08")
        self.day = Day08(filename="test_input.txt")

    def test_part_1_1(self):
        self.assertEqual(2, self.day.solve_part_1())

    def test_part_1_2(self):
        self.day = Day08(filename=self.dataPath / Path("test_input_2.txt"))
        self.assertEqual(6, self.day.solve_part_1())

    def test_part_2(self):
        self.day = Day08(filename=self.dataPath / Path("test_input_3.txt"))
        self.assertEqual(6, self.day.solve_part_2())
