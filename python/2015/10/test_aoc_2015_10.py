import unittest
import aoc_2015_10 as a


class Test_2015_10(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2015, 10))

    def test_part_1(self):
        self.assertEqual(6, a.solve_part_1(self.data, loops=4))

    def test_part_1_1(self):
        self.assertEqual(4, a.solve_part_1('211', loops=1))
