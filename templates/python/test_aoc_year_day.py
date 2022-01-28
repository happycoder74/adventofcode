import unittest
import aoc_<YEAR>_<DAY> as a


class Test_year_day(unittest.TestCase):
    def setUp(self):
        self.data = a.get_input("test_input.txt", <YEAR>, <CORR_DAY>)

    def test_part_1(self):
        self.assertEqual(None, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(None, a.solve_part_2(self.data))
