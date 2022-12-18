import unittest
import aoc_2016_07 as a


class Test_2016_07(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2016, 7))

    def test_part_1(self):
        self.assertEqual(2, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(3, a.solve_part_2(self.data))
