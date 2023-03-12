import unittest
import aoc_2016_03 as a


class Test_2016_03(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(a.get_input("test_input.txt", 2016, 3))

    def test_part_1(self):
        self.assertEqual(0, a.solve_part_1(self.data))

    def test_part_2(self):
        data = a.clean_input("""
        101 301 501
        102 302 502
        103 303 503
        201 401 601
        202 402 602
        203 403 603
        """.strip().splitlines())

        self.assertEqual(6, a.solve_part_2(data))
