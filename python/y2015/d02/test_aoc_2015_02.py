import unittest
import aoc_2015_02 as a


class Test_2015_02(unittest.TestCase):
    def setUp(self):
        pass

    def test_part_1(self):
        data = [[2,  3, 4]]
        self.assertEqual(58, a.solve_part_1(data))

    def test_part_2(self):
        data = [[2,  3, 4]]
        self.assertEqual(34, a.solve_part_2(data))
