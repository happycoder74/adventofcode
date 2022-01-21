import unittest
import aoc_year_day as a


class Test_year_day(unittest.TestCase):

    def test_part_1(self):
        data = a.get_input("test_input.txt")
        self.assertEqual(None, a.solve_part_1(data))

    def test_part_2(self):
        data = a.get_input("test_input.txt")
        self.assertEqual(None, a.solve_part_2(data))
