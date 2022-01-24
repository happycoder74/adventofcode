import unittest
import aoc_2015_01 as a


class Test_2015_01(unittest.TestCase):

    def test_part_1(self):
        data = ')())())'
        self.assertEqual(-3, a.solve_part_1(data))

    def test_part_2(self):
        data = '()())'
        self.assertEqual(5, a.solve_part_2(data))
