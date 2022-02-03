import unittest
import aoc_2021_11 as a


class Test_2021_11(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", 2021, 11)
        )

    def test_part_1(self):
        self.assertEqual(204, a.solve_part_1(self.data, 10))

    def test_part_1_100(self):
        self.assertEqual(1656, a.solve_part_1(self.data, 100))

    def test_part_2(self):
        self.assertEqual(195, a.solve_part_2(self.data))
