from collections import defaultdict

from common import Puzzle, timer


class Day05(Puzzle, year=2024, day=5):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.links = self.data[0]
        self.updates = self.data[1]

    @staticmethod
    def clean_input(data) -> tuple[dict[int, set[int]], list[str]]:
        links = defaultdict(set)
        rules = []
        updates = []
        for line in data:
            if "|" in line:
                node, target = line.split("|")
                rules.append((int(node), int(target)))
            elif line != "":
                updates.append([int(val) for val in line.split(",")])

        for node, target in rules:
            links[node].add(target)
        return (links, updates)

    def is_right_order(self, update):
        right_order = True
        for index in range(len(update)):
            node = update[index]
            if node not in self.links.keys():
                continue

            for target in update[:index]:
                if target in self.links[node]:
                    right_order = False
                    break
            if not right_order:
                break
        return right_order

    def reorder(self, update):
        order = {value: len(set(update) & self.links[value]) for value in update}
        ordered_list = sorted(order.items(), reverse=True, key=lambda p: p[1])
        return [p[0] for p in ordered_list]

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        result = 0

        for update in self.updates:
            if self.is_right_order(update):
                result += update[len(update) // 2]

        return result

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        result = 0
        for update in self.updates:
            if not self.is_right_order(update):
                sorted_update = self.reorder(update)
                result += sorted_update[len(sorted_update) // 2]
        return result
