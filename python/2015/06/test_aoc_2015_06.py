import unittest
import aoc_2015_06 as a


class Test_2015_06(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2015, 6))

    def test_part_1(self):
        self.assertEqual(1000, a.solve_part_1(self.data))

    def test_part_2(self):
        data = [('toggle', (0, 1000), (0, 1000))]
        self.assertEqual(2000000, a.solve_part_2(data))
