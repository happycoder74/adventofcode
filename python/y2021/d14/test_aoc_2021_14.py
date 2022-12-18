import unittest
import aoc_2021_14 as a


class Test_2021_14(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", 2021, 14)
        )

    def test_part_1(self):
        answer = "NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB"
        self.assertEqual(1588, a.solve_part_1(self.data))
        self.assertEqual(answer, a.solve_part_1(self.data, 4))

    def test_part_2(self):
        self.assertEqual(1588, a.solve_part_2(self.data, 10))
        self.assertEqual(2188189693529, a.solve_part_2(self.data))
