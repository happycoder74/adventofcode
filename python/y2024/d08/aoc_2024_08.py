from collections import defaultdict
from itertools import combinations

from common import Puzzle, timer


class Day08(Puzzle, year=2024, day=8):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.limits = self.data[1]
        self.antennas = self.data[0]

    @staticmethod
    def clean_input(data) -> tuple[dict[str, list[tuple[int, int]]], tuple[int, int]]:
        antennas = defaultdict(list)
        for row, line in enumerate(data):
            for col, char in enumerate(line):
                if char != ".":
                    antennas[char].append((row, col))

        limits = (len(data), len(data[0]))
        return antennas, limits

    def in_bound(self, location: tuple[int, int]) -> bool:
        return (0 <= location[0] < self.limits[0]) and (0 <= location[1] < self.limits[1])

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        self.antinodes = set()
        for _, antennas in self.antennas.items():
            offsets = [(v[0][0] - v[1][0], v[0][1] - v[1][1]) for v in combinations(antennas, r=2)]
            for offset, pair in zip(offsets, combinations(antennas, r=2)):
                d_row = pair[0][0] + offset[0]
                d_col = pair[0][1] + offset[1]
                if self.in_bound((d_row, d_col)):
                    self.antinodes.add((d_row, d_col))
                d_row = pair[1][0] - offset[0]
                d_col = pair[1][1] - offset[1]
                if self.in_bound((d_row, d_col)):
                    self.antinodes.add((d_row, d_col))

        return len(self.antinodes)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        self.antinodes = set()
        for _, antennas in self.antennas.items():
            for pair in combinations(antennas, r=2):
                self.antinodes.add(pair[0])
                self.antinodes.add(pair[1])
                offset = (pair[0][0] - pair[1][0], pair[0][1] - pair[1][1])
                d_row = pair[0][0] + offset[0]
                d_col = pair[0][1] + offset[1]
                while self.in_bound((d_row, d_col)):
                    self.antinodes.add((d_row, d_col))
                    d_row += offset[0]
                    d_col += offset[1]

                d_row = pair[1][0] - offset[0]
                d_col = pair[1][1] - offset[1]
                while self.in_bound((d_row, d_col)):
                    self.antinodes.add((d_row, d_col))
                    d_row -= offset[0]
                    d_col -= offset[1]

        return len(self.antinodes)
