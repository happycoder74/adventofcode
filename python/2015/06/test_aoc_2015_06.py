import unittest
import aoc_2015_6 as a


class Test_2015_6(unittest.TestCase):

    def test_part_1(self):
        data = a.get_input("test_input.txt")
        self.assertEqual(1000, a.solve_part_1(data))

    def test_part_2(self):
        data = [('toggle', (0, 1000), (0, 1000))]
        self.assertEqual(2000000, a.solve_part_2(data))
