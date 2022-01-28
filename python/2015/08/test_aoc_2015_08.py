import unittest
import aoc_2015_08 as a


class Test_2015_08(unittest.TestCase):
    def setUp(self):
        self.data = a.get_input("test_input.txt", 2015, 8)

    def test_part_1(self):
        self.assertEqual(12, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(19, a.solve_part_2(self.data))
