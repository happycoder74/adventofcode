import sys
from common import timer, Puzzle


def prio(char: str):
    if char.isupper():
        return ord(char) - ord('A') + 27
    return ord(char) - ord('a') + 1


class Day3(Puzzle, year=2022, day=3):
    @staticmethod
    def clean_input(data):
        rucksacks = list()
        for r in data:
            row = r.strip()
            rucksacks.append((row[0:int(len(row)/2)], row[int(len(row)/2):]))
        return rucksacks

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        prio_sum = 0
        for item1, item2 in self.data:
            set_of_items = set(item1).intersection(set(item2))
            for common_item in set_of_items:
                prio_sum += prio(common_item)
        return prio_sum

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        groups = list()
        group = list()

        for group_index, pack in enumerate(self.data):
            group.append(''.join(pack))
            if ((group_index + 1) % 3) == 0 and group_index > 0:
                groups.append(group)
                group = list()

        prio_sum = 0
        for group in groups:
            group_set = set(group[0])
            for member in group[1:]:
                group_set = group_set.intersection(set(member))
            prio_sum += prio(group_set.pop())

        return prio_sum


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day3(filename=filename).solve_all()
