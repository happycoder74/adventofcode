import unittest
import aoc_2015_09 as a


class Test_2015_09(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2015, 9))

    def test_part_1(self):
        self.assertEqual(605, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(982, a.solve_part_2(self.data))
