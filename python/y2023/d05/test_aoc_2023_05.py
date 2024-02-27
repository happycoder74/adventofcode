import unittest
from aoc_2023_05 import Day05


class Test_2023_05(unittest.TestCase):
    def setUp(self):
        self.day = Day05(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(35, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(46, self.day.solve_part_2())

    def test_match_range(self):
        source_range = [(55, 68), (79, 93)]
        destination_map = {52: (50, 48), 50: (98, 2)}
        destination_range = [(57, 70), (81, 95)]
        result = self.day.match_range(destination_map, source_range)
        self.assertEqual(destination_range, list(result.values()))
