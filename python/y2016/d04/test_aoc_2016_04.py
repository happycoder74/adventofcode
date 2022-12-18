import unittest
import aoc_2016_04 as a


class Test_2016_04(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2016, 4))

    def test_part_1(self):
        self.assertEqual(1514, a.solve_part_1(self.data[:-1]))

    def test_part_2(self):
        self.assertEqual(343, a.solve_part_2(self.data, check_string="very"))
