from common import timer, Puzzle


class Day04(Puzzle, year=2023, day=4):
    @staticmethod
    def clean_input(data):
        return [d[9:].split("|") for d in data]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return sum(
            [
                v
                for v in [
                    2 ** (len(set(card[1].split()).intersection(set(card[0].split()))) - 1)
                    for card in self.data
                ]
                if v >= 1
            ]
        )

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        deck = [0] * len(self.data)
        for i, card in enumerate(self.data):
            deck[i] += 1
            wins = set(card[1].split()).intersection(set(card[0].split()))
            for j in range(0, len(wins)):
                deck[i + j + 1] += deck[i]
        return sum(deck)
