import unittest
import aoc_2020_03 as a


class Test_2020_03(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", 2020, 3)
        )

    def test_part_1(self):
        self.assertEqual(None, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(None, a.solve_part_2(self.data))
