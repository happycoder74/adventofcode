import unittest
import aoc_2017_01 as a


class Test_2017_1(unittest.TestCase):
    def setUp(self):
        self.data = [
            ['1122',
             '1111',
             '1234',
             '91212129'],
            ['1212',
             '1221',
             '123425',
             '123123',
             '12131415']
        ]

    def test_part_1(self):
        ans = [3, 4, 0, 9]
        for i, v in enumerate(self.data[0]):
            self.assertEqual(ans[i], a.solve_part_1(v))

    def test_part_2(self):
        ans = [6, 0, 4, 12, 4]
        for i, v in enumerate(self.data[1]):
            self.assertEqual(ans[i], a.solve_part_2(v))
