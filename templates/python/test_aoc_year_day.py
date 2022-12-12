import unittest
from aoc_<YEAR>_<DAY> import Day<DAY>


class Test_<YEAR>_<DAY>(unittest.TestCase):
    def setUp(self):
        self.day = Day<DAY>(filename="test_input.txt")

    def test_part_1(self):
        self.assertEqual(None, self.day.solve_part_1())

    def test_part_2(self):
        self.assertEqual(None, self.day.solve_part_2())
