import unittest
import aoc_2016_8 as a


class Test_2016_8(unittest.TestCase):

    def test_part_1(self):
        data = a.get_input("test_input.txt")
        self.assertEqual(None, a.solve_part_1(data))

    def test_part_2(self):
        data = a.get_input("test_input.txt")
        self.assertEqual(None, a.solve_part_2(data))
