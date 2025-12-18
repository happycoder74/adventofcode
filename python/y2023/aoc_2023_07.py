from collections import Counter

from common import Puzzle, timer


class Day07(Puzzle, year=2023, day=7):
    def __init__(self, filename=None, data=None) -> None:
        super().__init__(filename=filename, data=data)
        self.strengths = {v: strength for strength, v in enumerate(list("23456789TJQKA"), start=2)}

    @staticmethod
    def clean_input(data):
        return {d.split()[0]: int(d.split()[1]) for d in data}

    @staticmethod
    def fixJ(cards):
        for card in cards:
            ranks = card[1]
            for i, rank in enumerate(ranks):
                if rank[0] == "J":
                    if i != 0:
                        ranks[0] = (ranks[0][0], ranks[0][1] + rank[1])
                        ranks[i] = (rank[0], 0)
                    elif rank[1] != 5:
                        ranks[1] = (ranks[1][0], ranks[1][1] + rank[1])
                        ranks[i] = (rank[0], 0)
                    break
            if ("J", 0) in ranks:
                _ = ranks.pop(ranks.index(("J", 0)))
        return cards

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        winnings = 0

        cards = [
            (h[0], sorted(Counter(h[0]).values(), reverse=True), int(h[1]))
            for h in self.data.items()
        ]
        game = sorted(cards, key=lambda c: [c[1]] + [self.strengths[ch] for ch in c[0]])

        winnings = sum([g[2] * (i + 1) for i, g in enumerate(game)])
        return winnings

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""

        self.strengths["J"] = 1
        cards = [
            (h[0], sorted(Counter(h[0]).items(), key=lambda it: it[1], reverse=True), int(h[1]))
            for h in self.data.items()
        ]
        cards = Day07.fixJ(cards)
        game = sorted(
            cards,
            key=lambda c: [
                sorted([v for _, v in c[1]], reverse=True),
                [self.strengths[ch] for ch in c[0]],
            ],
        )

        winnings = sum(g[2] * (i + 1) for i, g in enumerate(game))
        return winnings
