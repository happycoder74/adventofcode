import unittest

from aoc_2015_05 import Day05


class Test_2015_05(unittest.TestCase):
    def setUp(self):
        self.data: list[str] = [
            "ugknbfddgicrmopn",
            "aaa",
            "jchzalrnumimnmhp",
            "haegwjzuvuyypxyu",
            "dvszwmarrgswjxmb",
        ]

    def test_check_wovels_ok(self):
        self.data: list[str] = ["aeiouaeiouaeiou", "aei", "xazegov"]
        result = all([Day05.check_wovels(line) for line in self.data])
        self.assertTrue(result)

    def test_check_wovels_fail(self):
        self.data: list[str] = [
            "dvszwmarrgswjxmb",
        ]
        result = any([Day05.check_wovels(line) for line in self.data])
        self.assertFalse(result)

    def test_check_double_letter_ok(self):
        self.data: list[str] = ["xx", "abcdde", "aabbccdd"]
        result = all([Day05.check_dbl_letter(line) for line in self.data])
        self.assertTrue(result)

    def test_part_1_3(self):
        data = ["jchzalrnumimnmhp", "haegwjzuvuyypxyu", "dvszwmarrgswjxmb"]
        self.assertEqual(0, Day05(data=data).solve_part_1())

    def test_is_nice(self) -> None:
        line: str = "ugknbfddgicrmopn"
        self.assertTrue(Day05.is_nice(line))

    def test_is_nice_fail(self) -> None:
        line: str = "jchzalrnumimnmhp"
        self.assertFalse(Day05.is_nice(line))

    def test_is_nice2(self) -> None:
        lines: list[str] = [
            "qjhvhtzxzqqjkmpb",
            "xxyxx",
        ]
        result = all(Day05.is_nice_2(line) for line in lines)
        self.assertTrue(result)

    def test_is_nice2_false(self) -> None:
        lines: list[str] = ["uurcxstgmygtbst", "ieodomkazucvgmu"]
        result = any(Day05.is_nice_2(line) for line in lines)
        self.assertFalse(result)

    def test_part_1(self):
        result = Day05(data=self.data).solve_part_1()
        self.assertEqual(2, result[0])

    def test_part_2(self):
        data = ["qjhvhtzxzqqjkmpb" "xxyxx", "uurcxstgmygtbstg", "ieodomkazucvgmuy"]
        filename: str = "../data/2015/05/test_input_part_2.txt"
        self.assertEqual(2, Day05(filename=filename).solve_part_2())
