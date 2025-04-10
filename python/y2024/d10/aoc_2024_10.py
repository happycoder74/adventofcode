from collections import defaultdict, deque

from common import Puzzle, timer


class Node:
    def __init__(self, state):
        self.state = state


class Trail:
    def __init__(
        self,
        data: list[list[int]],
        start: list[tuple[int, int]],
        end: list[tuple[int, int]],
        part=1,
    ):
        self.height = len(data)
        self.width = len(data[0])
        self.data = data
        self.goal = end
        self.start = start
        self.part = part

    def neighbors(self, state):
        row, col = state
        candidates = [
            (row - 1, col),
            (row + 1, col),
            (row, col - 1),
            (row, col + 1),
        ]

        result = []
        for r, c in candidates:
            if (
                0 <= r < self.height
                and 0 <= c < self.width
                and (self.data[r][c] - self.data[row][col] == 1)
            ):
                result.append((r, c))
        return result

    def solve(self, part: int):
        result = 0
        for start in self.start:
            queue = deque()
            queue.append(Node(state=start))

            explored = set()

            while len(queue) > 0:
                # Using DFS since BFS while being faster yields the wrong result for part 2.
                node = queue.pop()

                if part == 1:
                    if node.state in explored:
                        continue
                    else:
                        explored.add(node.state)
                if node.state in self.goal:
                    result += 1
                    continue
                for state in self.neighbors(node.state):
                    if not any(node.state == state for node in queue):
                        child = Node(state=state)
                        queue.append(child)

        return result


class Day10(Puzzle, year=2024, day=10):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.start = self.data[0]
        self.end = self.data[1]
        self.trails = self.data[2]

    @staticmethod
    def clean_input(data):
        start = []
        end = []
        trails = []
        for irow, row in enumerate(data):
            trails.append([int(v) for v in row])
            for icol, column in enumerate(row):
                if column == "0":
                    start.append((irow, icol))
                elif column == "9":
                    end.append((irow, icol))

        return (start, end, trails)

    @timer(part=1)
    def solve_part_1(self) -> int:
        self.trail = Trail(self.trails, self.start, self.end)
        return self.trail.solve(part=1)

    @timer(part=2)
    def solve_part_2(self):
        self.trail = Trail(self.trails, self.start, self.end)
        return self.trail.solve(part=2)
