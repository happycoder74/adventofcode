from common import timer, Puzzle


class Day01(Puzzle, year=2019, day=1):
    @staticmethod
    def clean_input(data: list[str]) -> list[int]:
        return [int(d) for d in data]

    @staticmethod
    def calc_fuel(mass) -> int:
        fuel: int = mass // 3 - 2
        if fuel < 0:
            return 0
        else:
            return fuel + Day01.calc_fuel(fuel)

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        self.data: list[int]
        return sum([(m // 3 - 2) for m in self.data])

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        sum_fuel: int = 0
        for mass in self.data:
            fuel: int = mass // 3 - 2
            sum_fuel += fuel + Day01.calc_fuel(fuel)

        return sum_fuel
