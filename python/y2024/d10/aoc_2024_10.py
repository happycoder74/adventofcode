from collections import defaultdict, deque

from common import Puzzle, timer


class Node:
    def __init__(self, state, parent, action):
        self.state = state
        self.parent = parent
        self.action = action


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
        self.goal = end
        self.start = start
        self.contents = data.copy()
        self.solution = defaultdict(list)
        self.part = part

    def neighbors(self, state):
        row, col = state
        candidates = [
            ("up", (row - 1, col)),
            ("down", (row + 1, col)),
            ("left", (row, col - 1)),
            ("right", (row, col + 1)),
        ]

        result = []
        for action, (r, c) in candidates:
            if (
                0 <= r < self.height
                and 0 <= c < self.width
                and (self.contents[r][c] - self.contents[row][col] == 1)
            ):
                result.append((action, (r, c)))
        return result

    def solve(self):
        result = 0
        for start in self.start:
            queue = deque()
            queue.extend([Node(state=start, parent=None, action=None)])

            explored = set()
            reached = set()

            while True:
                if len(queue) == 0:
                    break

                # Using DFS since BFS while being faster yields the wrong result for part 2.
                node = queue.pop()

                if node.state in self.goal:
                    reached.add(node.state)
                    actions = []
                    cells = []
                    while node.parent is not None:
                        actions.append(node.action)
                        cells.append(node.state)
                        node = node.parent
                    actions.append(node.action)
                    cells.append(node.state)
                    actions.reverse()
                    cells.reverse()
                    self.solution[start].append(cells)
                else:
                    explored.add(node.state)
                    for action, state in self.neighbors(node.state):
                        if not any(node.state == state for node in queue):
                            child = Node(state=state, parent=node, action=action)
                            queue.append(child)

            result += len(reached)

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

        return self.trail.solve()

    @timer(part=2)
    def solve_part_2(self):
        res = 0
        for v in self.trail.solution.values():
            res += len(v)
        return res
