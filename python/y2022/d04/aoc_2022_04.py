from common import timer, Puzzle


class Day04(Puzzle, year=2022, day=4):
    @staticmethod
    def clean_input(data):
        elves = list()
        for row in data:
            pair = row.strip().split(",")
            p0min, p0max = map(int, pair[0].split("-"))
            p1min, p1max = map(int, pair[1].split("-"))
            elves.append(
                [
                    list(range(p0min, p0max + 1)),
                    list(range(p1min, p1max + 1))
                ]
            )

        return elves

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        overlaps = 0
        for pair1, pair2 in self.data:
            if (
                all(x in pair2 for x in pair1)
                or all(x in pair1 for x in pair2)
            ):
                overlaps += 1

        return overlaps

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        overlaps = 0
        for pair1, pair2 in self.data:
            if any(x in pair2 for x in pair1) or any(
                x in pair1 for x in pair2
            ):
                overlaps += 1

        return overlaps
