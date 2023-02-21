import unittest
from aoc_2019_01 import Day01 as Day


class Test_2019_01(unittest.TestCase):
    def setUp(self):
        self.data = [
            "100756"
        ]

    def test_clean_input(self) -> None:
        self.assertEqual([100756], Day.clean_input(self.data))

    def test_calc_fuel_negative(self) -> None:
        self.assertEqual(0, Day.calc_fuel(0))

    def test_part_1(self) -> None:
        self.assertEqual(33583, Day(data=self.data).solve_part_1())

    def test_part_2(self) -> None:
        self.assertEqual(50346, Day(data=self.data).solve_part_2())


if __name__ == "__main__":
    Test_2019_01().run()
