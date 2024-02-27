import functools
import math
from itertools import cycle

from common import Puzzle, timer


class Day08(Puzzle, year=2023, day=8):
    @staticmethod
    def clean_input(data):
        network = dict()
        for node in data[2:]:
            network[node[0:3]] = (node[7:10], node[12:15])
        return_data = (data[0], network)
        return return_data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        steps = cycle(self.data[0])
        step_index = 0
        found = False
        map = self.data[1]

        destination = map["AAA"]
        while not found:
            step = next(steps)
            step_index += 1
            if step == "R":
                new_node = destination[1]
            else:
                new_node = destination[0]
            if new_node == "ZZZ":
                found = True
            else:
                destination = map[new_node]

        return step_index

    @staticmethod
    def get_steps(node, instructions, network):
        steps_required = 0
        steps = cycle(instructions)
        step_index = 0
        while True:
            step = next(steps)
            step_index += 1
            if step == "R":
                node = network[node][1]
            else:
                node = network[node][0]

            if node.endswith("Z"):
                steps_required = step_index
                break

        return steps_required

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        steps_required = dict()
        instructions = self.data[0]
        network = self.data[1]
        nodes = [node for node in network if node.endswith("A")]
        for node in nodes:
            steps_required[node] = Day08.get_steps(node, instructions, network)

        return functools.reduce(math.lcm, steps_required.values())
