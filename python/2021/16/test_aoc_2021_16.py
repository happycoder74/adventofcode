import unittest
import aoc_2021_16 as a


class Test_2021_16(unittest.TestCase):
    def setUp(self):
        self.data = ""

    def test_part_1(self):
        data = [
            "D2FE28",
            "EE00D40C823060",
            "8A004A801A8002F478",
            "620080001611562C8802118E34",
            "C0015000016115A2E0802F182340",
            "A0016C880162017C3686B18A3D4780"
        ]

        answers = [
            6,
            14,
            16,
            12,
            23,
            31
        ]

        for d, ans in zip(data, answers):
            self.assertEqual(ans, a.solve_part_1(d))

    def test_part_2(self):
        self.assertEqual(None, a.solve_part_2(self.data))
