import unittest
import aoc_2021_09 as a


class Test_2021_09(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", 2021, 9)
        )

    def test_part_1(self):
        self.assertEqual(15, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(1134, a.solve_part_2(self.data))
