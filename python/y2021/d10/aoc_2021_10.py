from common import timer, Puzzle


class Day10(Puzzle, year=2021, day=10):
    @staticmethod
    def clean_input(data):
        return data

    def define_scores(self):
        brackets = {"(": ")", "[": "]", "{": "}", "<": ">"}
        invalid_score = {")": 3, "]": 57, "}": 1197, ">": 25137}
        incomplete_score = {")": 1, "]": 2, "}": 3, ">": 4}

        return {
            "brackets": brackets,
            "invalid_score": invalid_score,
            "incomplete_score": incomplete_score,
        }

    def invalid_incomplete(self, lines):
        scores = self.define_scores()
        brackets = scores["brackets"]

        invalid = []
        incomplete = []
        for line in lines:
            valid = True
            open_bracket = []
            for c in line:
                if c in brackets.keys():
                    open_bracket.append(c)
                if c in brackets.values():
                    if c != brackets[open_bracket[-1]]:
                        invalid.append(c)
                        valid = False
                        break
                    else:
                        _ = open_bracket.pop()
            if valid:
                incomplete.append(open_bracket)

        return (invalid, incomplete)

    @timer(part=1)
    def solve_part_1(self):

        scores = self.define_scores()
        invalid_score = scores["invalid_score"]

        invalid, incomplete = self.invalid_incomplete(self.data)
        total_score = 0
        for c in invalid:
            total_score += invalid_score[c]

        return total_score

    @timer(part=2)
    def solve_part_2(self):
        scores = self.define_scores()

        brackets = scores["brackets"]
        incomplete_score = scores["incomplete_score"]

        invalid, incomplete = self.invalid_incomplete(self.data)

        total_scores = [0 for i in incomplete]
        for index, line in enumerate(incomplete):
            line.reverse()
            for c in line:
                x = brackets[c]
                total_scores[index] = (
                    total_scores[index] * 5 + incomplete_score[x]
                )

        total_scores.sort()
        middle = int((len(total_scores) - 1) / 2)
        middle_score = total_scores[middle]

        return middle_score
