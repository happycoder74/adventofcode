import unittest
import aoc_2015_04 as a


class Test_2015_04(unittest.TestCase):

    def test_part_1(self):
        data = "abcdef"
        self.assertEqual(609043, a.solve_part_1(data))

    def test_part_1_1(self):
        data = "pqrstuv"
        self.assertEqual(1048970, a.solve_part_1(data))
