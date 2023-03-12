import sys
from common import timer, Puzzle
from collections import deque


class Node():
    def __init__(self, state, parent, action):
        self.state = state
        self.parent = parent
        self.action = action


class Trail():
    def __init__(self,
                 data: list = None,
                 start: list = None,
                 end: tuple = None):
        self.height = len(data)
        self.width = len(data[0])
        self.start = start
        self.goal = end

        self.contents = data.copy()
        self.solution = None

    def neighbors(self, state):
        row, col = state
        candidates = [
            ("up", (row - 1, col)),
            ("down", (row + 1, col)),
            ("left", (row, col - 1)),
            ("right", (row, col + 1))
        ]

        result = []
        for action, (r, c) in candidates:
            if (
                0 <= r < self.height
                and 0 <= c < self.width
                and (self.contents[r][c] - self.contents[row][col] <= 1)
            ):
                result.append((action, (r, c)))
        return result

    def solve(self):
        # Initialize queue to just the starting position
        queue = deque()
        queue.extend(
            [Node(state=s, parent=None, action=None) for s in self.start]
        )

        self.explored = set()

        while True:
            if len(queue) == 0:
                self.solution = None
                return

            node = queue.popleft()
            if node.state == self.goal:
                actions = []
                cells = []
                while node.parent is not None:
                    actions.append(node.action)
                    cells.append(node.state)
                    node = node.parent
                actions.reverse()
                cells.reverse()
                self.solution = (actions, cells)
                return

            self.explored.add(node.state)
            for action, state in self.neighbors(node.state):
                if (
                    not any(node.state == state for node in queue)
                    and state not in self.explored
                ):
                    child = Node(state=state, parent=node, action=action)
                    queue.append(child)

    def print(self):
        solution = (self.solution[1]
                    if self.solution is not None else None)
        print()
        for i, row in enumerate(self.contents):
            for j, col in enumerate(row):
                if solution is not None and (i, j) in solution:
                    print("\u001b[32m*\u001b[0m", end="")
                elif (i, j) == self.start:
                    print("S", end="")
                elif (i, j) == self.goal:
                    print("E", end="")
                else:
                    print(chr(col), end="")
            print()
        print()


class Day12(Puzzle, year=2022, day=12):
    def clean_input(self, data):
        return_data = []
        for i, row in enumerate(data):
            if "S" in row:
                self.start = (i, row.index("S"))
            if "E" in row:
                self.end = (i, row.index("E"))
            return_data.append(
                [ord('a') if c == 'S' else
                 ord('z') if c == 'E' else
                 ord(c) for c in row]
            )
        return return_data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        trail = Trail(self.data, [self.start], self.end)
        trail.solve()
        return len(trail.solution[1])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        lowpoints = list()
        for i, row in enumerate(self.data):
            for j, col in enumerate(row):
                if col == ord('a'):
                    lowpoints.append((i, j))
        trail = Trail(self.data, lowpoints, self.end)
        trail.solve()

        return len(trail.solution[1])


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day12(filename=filename).solve_all()
