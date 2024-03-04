import itertools

from common import Puzzle, timer


def my_product(fill, m, repeat=1):
    pools = [tuple(fill)] * repeat
    result = [[]]
    for pool in pools:
        result = [x + [y] for x in result for y in pool]

    for prod in result:
        if sum([len(x) for x in prod]) <= m:
            yield tuple(prod)


class Day12(Puzzle, year=2023, day=12):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)

    @staticmethod
    def clean_input(data) -> list[tuple[str, list[int]]]:
        return [(s.split(" ")[0], [int(v) for v in s.split(" ")[1].split(",")]) for s in data]

    @staticmethod
    def possible_patterns(pattern, length) -> list:
        return_list: list[str] = list()
        m: int = length - (sum(pattern) + len(pattern) - 1)
        map_pattern: list[str] = [p * "#" + "." for p in pattern[:-1]] + [pattern[-1] * "#"]
        fill: list[str] = [i * "." for i in range(0, m + 1)]
        fills = my_product(fill, m, repeat=len(map_pattern))
        for f in fills:
            s = [a + b for a, b in zip(f, map_pattern)]
            string_pattern = "".join(s).ljust(length, ".")
            return_list.append(string_pattern)

        return return_list

    @staticmethod
    def match_patterns(row, patterns) -> int:
        num_ok = 0
        pattern_ok = True
        for pattern in patterns:
            for m in zip(row, pattern):
                if (m == (".", "#")) or (m == ("#", ".")):
                    pattern_ok = False
                    break
            if pattern_ok:
                num_ok += 1
            pattern_ok = True
        return num_ok

    @timer(part=1)
    def solve_part_1(self) -> int:
        return_sum: int = 0
        for row, pattern in self.data:
            row_length: int = len(row)
            patterns: list = Day12.possible_patterns(pattern, row_length)
            return_sum += Day12.match_patterns(row, patterns)
        return return_sum

    @timer(part=2)
    def solve_part_2(self) -> str:
        return "NOT IMPLEMENTED"
