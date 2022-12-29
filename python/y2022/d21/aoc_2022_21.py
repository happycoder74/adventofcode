import operator
from typing import Any, Callable
from common import timer, Puzzle


class Day21(Puzzle, year=2022, day=21):
    def __init__(self, filename=None, data=None) -> None:
        self.data: dict[str, (str | int)]
        super().__init__(filename=filename, data=data)
        self.operator: dict[str, Callable] = {
            "+": operator.add,
            "-": operator.sub,
            "*": operator.mul,
            "/": operator.truediv,
        }
        self.monkeys: dict[str, (str | int)] = self.data

    @staticmethod
    def clean_input(data) -> dict[str, (str | int)]:
        monkeys: dict[str, (str | int)] = {}
        for row in data:
            name: str
            job: str
            name, job = row.split(":")
            if job.strip().isnumeric():
                monkeys[name] = int(job)
            else:
                monkeys[name] = job.strip()
        return monkeys

    def solver(self, monkey, part=1) -> (str | float | int | None):
        if monkey == "humn" and part == 2:
            raise TypeError
        if isinstance(self.monkeys[monkey], int) or isinstance(
            self.monkeys[monkey], float
        ):
            return self.monkeys[monkey]
        else:
            monkey1, operation, monkey2 = self.monkeys[monkey].split(" ")
            return self.operator[operation](
                self.solver(monkey1, part=part),
                self.solver(monkey2, part=part),
            )

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        return int(self.solver("root"))

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        monkey1, _, monkey2 = self.monkeys["root"].split(" ")
        result = []
        res: Any = None
        monkeys = [monkey1, monkey2]
        for monkey in monkeys:
            try:
                res = self.solver(monkey, part=2)
            except TypeError:
                res = None
            finally:
                result.append(res)
        branch: int = result.index(None)
        yells: list[Any] = [0, result[1 if branch == 0 else 0]]
        values: list[Any] = []
        for yell in yells:
            self.monkeys["humn"] = int(yell)
            values.append(self.solver(monkeys[branch]))

        yell: int = int(
            (yells[1] - yells[0])
            / (values[1] - values[0])
            * (result[not branch] - values[0])
            + yells[0]
        )
        self.monkeys["humn"] = yell
        return yell
