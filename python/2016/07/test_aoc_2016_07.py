import unittest
import aoc_2016_07 as a


class Test_2016_7(unittest.TestCase):

    def test_part_1(self):
        data = a.get_input("test_input.txt", 2016, 7)
        self.assertEqual(2, a.solve_part_1(data))

    def test_part_2(self):
        data = a.get_input("test_input.txt", 2016, 7)
        self.assertEqual(3, a.solve_part_2(data))
