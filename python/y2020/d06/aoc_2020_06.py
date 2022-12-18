import sys
from common import timer, Puzzle


class Day06(Puzzle, year=2020, day=6):
    @staticmethod
    def clean_input(data):
        return Day06.parse_input_groups(data)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        sets = []
        for line in self.data:
            s = set()
            for c in line:
                s = s.union(set(c))
            sets.append(s)

        return sum([len(s) for s in sets])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        questions = []
        for group in self.data:
            persons = []
            for person in group:
                s = set()
                for c in person:
                    s.add(c)
                persons.append(s)
            q_set = persons[0]
            if len(persons) > 1:
                for person in persons[1:]:
                    q_set = q_set.intersection(person)
            questions.append(q_set)

        return sum([len(s) for s in questions])


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day06(filename=filename).solve_all()
