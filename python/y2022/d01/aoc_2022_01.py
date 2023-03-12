from common import timer, Puzzle


class Day01(Puzzle, year=2022, day=1):
    @staticmethod
    def clean_input(data):
        return [int(n) if n != '' else n for n in data]

    def elves(self):
        elves = Puzzle.parse_input_groups(self.data)
        return elves

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return max(map(sum, Puzzle.parse_input_groups(self.data)))

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        elves_list = list(map(sum, Puzzle.parse_input_groups(self.data)))
        elves_list.sort(reverse=True)
        return sum(elves_list[0:3])
