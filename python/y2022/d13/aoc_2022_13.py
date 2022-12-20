import json
import itertools
from common import timer, Puzzle
import functools


class Day13(Puzzle, year=2022, day=13):
    @staticmethod
    def clean_input(data):
        return_data = [json.loads(d) if d != '' else '' for d in data]
        return Puzzle.parse_input_groups(return_data)

    @staticmethod
    def compare(n1: list, n2: list) -> int:
        nodes: list
        nodes = [node
                 for node in itertools.zip_longest(n1, n2)]
        while nodes:
            left, right = nodes.pop(0)
            if left is None:
                return 1
            elif right is None:
                return -1
            if isinstance(left, int):
                if isinstance(right, int):
                    if left < right:
                        return 1
                    elif left > right:
                        return -1
                else:
                    nodes = [([left], right)] + nodes
            else:
                if isinstance(right, int):
                    nodes = [(left, [right])] + nodes
                else:
                    nodes = ([node for node in
                             itertools.zip_longest(left, right)] + nodes)
        return 0

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        right_order_indices = []
        for i, (n1, n2) in enumerate(self.data, start=1):
            if (Day13.compare(n1, n2) == 1):
                right_order_indices.append(i)
        return sum(right_order_indices)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        data = [[[2]], [[6]]]
        for row in self.data:
            data.extend((row[0], row[1]))

        sorted_list = sorted(data,
                             key=functools.cmp_to_key(Day13.compare),
                             reverse=True)

        return (sorted_list.index([[2]]) + 1) * (sorted_list.index([[6]]) + 1)

    @timer(part=2, title="Alt part 2 solution")
    def solve_part2_b(self):
        index2 = 1
        index6 = 2
        for row in self.data:
            for num in row:
                if Day13.compare([[2]], num) < 0:
                    index2 += 1
                if Day13.compare([[6]], num) < 0:
                    index6 += 1

        return index2 * index6

    @timer(part='main', title='Total elapsed', show_return=False)
    def solve_all(self):
        part1 = self.solve_part_1()
        part2 = self.solve_part_2()
        part2b = self.solve_part2_b()
        return part1, part2, part2b
