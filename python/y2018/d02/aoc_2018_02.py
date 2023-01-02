from collections import Counter
from common import timer, Puzzle


class Day02(Puzzle, year=2018, day=2):
    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        counters = [Counter(row) for row in self.data]
        twos = len([1 for n in counters if 2 in n.values()])
        threes = len([1 for n in counters if 3 in n.values()])
        return twos * threes

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return_value = ""
        for i, row in enumerate(self.data[:-1]):
            for row2 in self.data[i + 1 :]:
                check = [a for a, b in zip(row, row2) if a == b]
                if len(check) == len(row) - 1:
                    return_value = "".join(check)
        print(f"{return_value=}")
        return return_value
