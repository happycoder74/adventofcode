from collections import deque
from common import timer, Puzzle


class Day12(Puzzle, year=2021, day=12):
    @staticmethod
    def clean_input(data):
        connection_data = [
            [part for part in line.strip().split("-")] for line in data
        ]
        connections = {
            con[i]: set()
            for con in connection_data
            for i in [0, 1]
            if con[i] != "end"
        }
        for con in connection_data:
            if (con[1] != "start") and (con[0] != "end"):
                connections[con[0]].add(con[1])
            if (con[0] != "start") and (con[1] != "end"):
                connections[con[1]].add(con[0])

        return connections

    def solver(self, twice=False):
        paths = []
        to_visit = deque()
        to_visit.append(("start", [], False))

        while to_visit:
            node, path, small_visited = to_visit.popleft()
            if node == "end":
                path.append(node)
                paths.append(path)
            else:
                for next_node in self.data.get(node, list()):
                    if (
                        next_node.isupper()
                        or next_node not in path
                        or (twice and not small_visited)
                    ):
                        v = small_visited or (
                            next_node.islower() and next_node in path
                        )
                        to_visit.appendleft((next_node, path + [node], v))

        return paths

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        solution = self.solver()
        return len(solution)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        solution = self.solver(twice=True)
        return len(solution)
