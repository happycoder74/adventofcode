import unittest
import aoc_<YEAR>_<DAY> as a


class Test_year_day(unittest.TestCase):

    def test_part_1(self):
        data = a.get_input("test_input.txt", <YEAR>, <CORR_DAY>)
        self.assertEqual(None, a.solve_part_1(data))

    def test_part_2(self):
        data = a.get_input("test_input.txt", <YEAR>, <CORR_DAY>)
        self.assertEqual(None, a.solve_part_2(data))
