import re
from collections import deque

import numpy as np
from common import Puzzle, timer


class Day13(Puzzle, year=2024, day=13):
    @staticmethod
    def clean_input(data) -> list[list[int]]:
        pattern = re.compile(r"\d+")
        return [[int(v) for v in pattern.findall(line.strip())] for line in data if line.strip()]

    @timer(part=1)
    def solve_part_1a(self) -> int:
        return self.solver_a()

    @timer(part=1)
    def solve_part_1b(self) -> int:
        return self.solver_b()

    @timer(part=2)
    def solve_part_2a(
        self,
    ) -> int:
        return self.solver_a(delta=10_000_000_000_000)

    @timer(part=1)
    def solve_part_2b(self) -> int:
        return self.solver_b(delta=10_000_000_000_000)

    def solver_a(self, delta=0) -> int:
        eps = 0.001
        result = 0
        equations = deque(self.data)

        while equations:
            A = np.transpose(np.array([equations.popleft() for _ in range(2)]))
            B = np.array([v + delta for v in equations.popleft()])
            res = np.matmul(np.linalg.inv(A), B)
            if (abs(res[0] - np.round(res[0])) < eps) and (abs(res[1] - np.round(res[1])) < eps):
                result += res[0] * 3 + res[1]

        return int(result)

    def solver_b(self, delta=0) -> int:
        result = 0
        equations: deque[list[int]] = deque(self.data)

        while equations:
            x0, y0 = equations.popleft()
            x1, y1 = equations.popleft()
            Cx, Cy = equations.popleft()
            Cx, Cy = Cx + delta, Cy + delta
            a_presses, a_remainder = divmod(Cx * y1 - Cy * x1, y1 * x0 - x1 * y0)
            if a_remainder:
                continue
            b_presses, b_remainder = divmod(-Cx * y0 + Cy * x0, y1 * x0 - x1 * y0)
            if b_remainder:
                continue
            result += 3 * a_presses + b_presses

        return result

    def solve_part_1(self):
        self.solve_part_1a()
        self.solve_part_1b()

    def solve_part_2(self):
        self.solve_part_2a()
        self.solve_part_2b()
