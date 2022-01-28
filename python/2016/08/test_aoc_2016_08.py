import unittest
import aoc_2016_08 as a


class Test_2016_08(unittest.TestCase):

    def test_part_1(self):
        data = a.clean_input(a.get_input("test_input.txt", 2016, 08))
        self.assertEqual(None, a.solve_part_1(data))

    def test_part_2(self):
        data = a.clean_input(a.get_input("test_input.txt", 2016, 08))
        self.assertEqual(None, a.solve_part_2(data))
