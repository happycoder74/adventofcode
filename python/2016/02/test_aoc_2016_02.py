import unittest
import aoc_2016_02 as a


class Test_2016_02(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2016, 2))

    def test_part_1(self):
        self.assertEqual('1985', a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual('5DB3', a.solve_part_2(self.data))
