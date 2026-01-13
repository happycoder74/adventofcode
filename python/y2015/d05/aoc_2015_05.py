from common import timer, Puzzle


class Day05(Puzzle, year=2015, day=5):
    @staticmethod
    def clean_input(data) -> bool:
        return data

    @staticmethod
    def check_wovels(line) -> bool:
        return sum([line.count(c) for c in "aeiou"]) >= 3

    @staticmethod
    def check_dbl_letter(line) -> bool:
        for i, a in enumerate(line[:-1]):
            if a == line[i + 1]:
                return True
        return False

    @staticmethod
    def check_invalid(line) -> bool:
        for p in ["ab", "cd", "pq", "xy"]:
            if p in line:
                return False
        return True

    @staticmethod
    def check_pairs(line) -> bool:
        zipped = list(zip(line, line[1:]))
        pairs: dict[tuple[str, str], int] = dict()
        for index, pair in enumerate(zipped):
            if pair not in pairs:
                pairs[pair] = index
                continue
            if pairs[pair] < index - 1:
                return True
        return False

    @staticmethod
    def check_repeat(line: str) -> bool:
        return any([a == b for a, b in zip(line, line[2:])])

    @staticmethod
    def is_nice(line) -> bool:
        return all(
            [
                Day05.check_wovels(line),
                Day05.check_dbl_letter(line),
                Day05.check_invalid(line),
            ]
        )

    @staticmethod
    def is_nice_2(line) -> bool:
        return all([Day05.check_pairs(line), Day05.check_repeat(line)])

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        return len(list(filter(Day05.is_nice, self.data)))

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        return len(list(filter(Day05.is_nice_2, self.data)))
