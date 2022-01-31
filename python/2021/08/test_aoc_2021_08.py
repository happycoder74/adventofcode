import unittest
import aoc_2021_08 as a


class Test_2021_08(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", 2021, 8)
        )

    def test_part_1(self):
        self.assertEqual(26, a.solve_part_1(self.data))

    def test_part_2(self):
        data = ' '.join(
            [
                "acedgfb cdfbe gcdfa fbcad dab cefabd",
                "cdfgeb eafb cagedb ab", "|", "cdfeb fcadb cdfeb cdbaf"
            ])
        self.assertEqual(5353, a.solve_part_2(a.clean_input([data])))

    def test_part_2_2(self):
        self.assertEqual(61229, a.solve_part_2(self.data))


