import unittest
from aoc_2015_05 import Day05


class Test_2015_05(unittest.TestCase):
    def setUp(self):
        self.data = [
            "ugknbfddgicrmopn",
            "aaa",
            "jchzalrnumimnmhp",
            "haegwjzuvuyypxyu",
            "dvszwmarrgswjxmb"
        ]

    def test_part_1(self):
        self.assertEqual(2, Day05(data=self.data).solve_part_1())

    def test_part_1_1(self):
        data = ["ugknbfddgicrmopn"]
        self.assertEqual(1, Day05(data=data).solve_part_1())

    def test_part_1_2(self):
        data = ["jchzalrnumimnmhp"]
        self.assertEqual(0, Day05(data=data).solve_part_1())

    def test_part_1_3(self):
        data = [
            "jchzalrnumimnmhp",
            "haegwjzuvuyypxyu",
            "dvszwmarrgswjxmb"
        ]
        self.assertEqual(0, Day05(data=data).solve_part_1())

    def test_is_nice(self) -> None:
        line: str = "ugknbfddgicrmopn"
        self.assertTrue(Day05.is_nice(line))

    def test_is_nice_false(self) -> None:
        line: str = "jchzalrnumimnmhp"
        self.assertFalse(Day05.is_nice(line))

    def test_is_nice2(self) -> None:
        line: str = "qjhvhtzxzqqjkmp"
        self.assertTrue(Day05.is_nice_2(line))

    def test_is_nice2_false(self) -> None:
        line: str = "uurcxstgmygtbst"
        self.assertFalse(Day05.is_nice_2(line))

    def test_is_nice2_1(self) -> None:
        line: str = "xxyxx"
        self.assertTrue(Day05.is_nice_2(line))

    def test_is_nice2_1_false(self) -> None:
        line: str = "ieodomkazucvgmu"
        self.assertFalse(Day05.is_nice_2(line))

    def test_part_2(self):
        data = [
            "qjhvhtzxzqqjkmpb"
            "xxyxx",
            "uurcxstgmygtbstg",
            "ieodomkazucvgmuy"
        ]
        filename: str = "../data/2015/05/test_input_part_2.txt"
        self.assertEqual(2,
                         Day05(filename=filename).solve_part_2())
