import unittest
from aoc_<YEAR>_<DAY> import Day<DAY> as a


class Test_<YEAR>_<DAY>(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", <YEAR>, <CORR_DAY>)
        )

    def test_part_1(self):
        self.assertEqual(None, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(None, a.solve_part_2(self.data))
