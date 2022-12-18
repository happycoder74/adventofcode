import unittest
import aoc_2016_06 as a


class Test_2016_06(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2016, 6))

    def test_part_1(self):
        self.assertEqual("easter", a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual("advent", a.solve_part_2(self.data))
