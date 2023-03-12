import unittest
import aoc_2016_08 as a


class Test_2016_08(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2016, 8))

    def test_part_1(self):
        self.assertEqual(6, a.solve_part_1(self.data))

    def test_part_1_1(self):
        self.assertEqual(9, a.solve_part_1(a.clean_input(['rect 3x3'])))

    def test_part_1_2(self):
        data = [
            'rect 9x6',
            'rotate row y=1 by 1'
        ]
        self.assertEqual(54, a.solve_part_1(a.clean_input(data)))
