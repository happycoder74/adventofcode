from common import Puzzle, timer


class Day04(Puzzle, year=2022, day=4):
    @staticmethod
    def clean_input(data):
        elves = list()
        for row in data:
            pair = row.strip().split(",")
            p0min, p0max = map(int, pair[0].split("-"))
            p1min, p1max = map(int, pair[1].split("-"))
            elves.append((p0min, p0max, p1min, p1max))

        return elves

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        overlaps = 0
        for p0min, p0max, p1min, p1max in self.data:
            if (p0min <= p1min) and (p1max <= p0max) or (p1min <= p0min) and (p0max <= p1max):
                overlaps += 1

        return overlaps

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        overlaps = 0
        for p0min, p0max, p1min, p1max in self.data:
            if (p1min <= p0min) and (p0min <= p1max) or (p0min <= p1min) and (p1min <= p0max):
                overlaps += 1

        return overlaps
