import unittest
import aoc_2016_01 as a


class Test_2016_01(unittest.TestCase):
    def setUp(self):
        pass

    def test_part_1(self):
        data = a.clean_input(["R5, L5, R5, R3"])
        self.assertEqual(12, a.solve_part_1(data))

    def test_part_2(self):
        data = a.clean_input(["R8, R4, R4, R8"])
        self.assertEqual(4, a.solve_part_2(data))
