import unittest
import aoc_2021_01 as a


class Test_2021_01(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2015, 1))

    def test_part_1(self):
        self.assertEqual(7,  a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(5,  a.solve_part_2(self.data))
