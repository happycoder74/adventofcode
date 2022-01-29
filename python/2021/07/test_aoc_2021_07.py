import unittest
import aoc_2021_07 as a


class Test_2021_07(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(["16,1,2,0,4,2,7,1,2,14"])

    def test_part_1(self):
        self.assertEqual(37, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(168, a.solve_part_2(self.data))
