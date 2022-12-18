from common import timer, Puzzle


class Day01(Puzzle, year=2019, day=1):
    @staticmethod
    def clean_input(data):
        return [int(d) for d in data]

    @staticmethod
    def calc_fuel(mass):
        fuel = int(mass / 3) - 2
        if fuel < 0:
            return 0
        else:
            return fuel + Day01.calc_fuel(fuel)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return sum([(int(m/3) - 2) for m in self.data])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        sum_fuel = 0
        for mass in self.data:
            fuel = int(mass / 3) - 2
            sum_fuel += fuel + Day01.calc_fuel(fuel)

        return sum_fuel
