import unittest
import aoc_2015_03 as a


class Test_2015_03(unittest.TestCase):

    def test_part_1(self):
        data = '^v^v^v^v^v'
        self.assertEqual(2, a.solve_part_1(data))

    def test_part_2(self):
        data = '^v^v^v^v^v'
        self.assertEqual(11, a.solve_part_2(data))
