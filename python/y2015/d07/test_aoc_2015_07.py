import unittest
import aoc_2015_07 as a


class Test_2015_07(unittest.TestCase):

    def test_part_1_1(self):
        data = [("123", "x")]
        self.assertEqual({"x": 123}, a.solve_part_1(data, return_key=None))

    def test_part_1(self):
        data = a.clean_input(a.get_input("test_input.txt", year=2015, day=7))
        answer = {
            "d": 72,
            "e": 507,
            "f": 492,
            "g": 114,
            "h": 65412,
            "i": 65079,
            "x": 123,
            "y": 456,
        }

        self.assertEqual(answer, a.solve_part_1(data, return_key=None))
