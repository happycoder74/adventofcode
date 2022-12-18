import sys
from common import timer, get_input


def clean_input(data):
    return data


def define_scores():
    brackets = {
        "(": ")",
        "[": "]",
        "{": "}",
        "<": ">"
    }

    invalid_score = {
        ")": 3,
        "]": 57,
        "}": 1197,
        ">": 25137
    }

    incomplete_score = {
        ")": 1,
        "]": 2,
        "}": 3,
        ">": 4
    }

    return {"brackets": brackets,
            "invalid_score": invalid_score,
            "incomplete_score": incomplete_score
            }


def invalid_incomplete(lines):

    scores = define_scores()
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
def solve_part_1(data):

    scores = define_scores()
    invalid_score = scores["invalid_score"]

    invalid, incomplete = invalid_incomplete(data)
    total_score = 0
    for c in invalid:
        total_score += invalid_score[c]

    return total_score


@timer(part=2)
def solve_part_2(data):
    scores = define_scores()

    brackets = scores["brackets"]
    incomplete_score = scores["incomplete_score"]

    invalid, incomplete = invalid_incomplete(data)

    total_scores = [0 for i in incomplete]
    for index, line in enumerate(incomplete):
        line.reverse()
        for c in line:
            x = brackets[c]
            total_scores[index] = total_scores[index] * 5 + incomplete_score[x]

    total_scores.sort()
    middle = int((len(total_scores) - 1) / 2)
    middle_score = total_scores[middle]

    return middle_score


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 10))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
