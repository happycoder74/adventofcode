import unittest
import aoc_2015_05 as a


class Test_2015_05(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2015, 5))

    def test_part_1(self):
        self.assertEqual(2, a.solve_part_1(self.data))

    def test_part_1_1(self):
        data = ["ugknbfddgicrmopn"]
        self.assertEqual(1, a.solve_part_1(data))

    def test_part_1_2(self):
        data = ["jchzalrnumimnmhp"]
        self.assertEqual(0, a.solve_part_1(data))

    def test_part_1_3(self):
        data = ["jchzalrnumimnmhp", "haegwjzuvuyypxyu", "dvszwmarrgswjxmb"]
        self.assertEqual(0, a.solve_part_1(data))

    def test_part_2(self):
        data = a.get_input("test_input_part_2.txt", 2015, 5)
        self.assertEqual(2, a.solve_part_2(data))
