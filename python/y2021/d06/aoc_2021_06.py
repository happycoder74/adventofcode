from common import timer, Puzzle


class LanternFish:
    def __init__(self, days_left=8):
        self.days_left = days_left

    def spawn(self):
        if self.days_left == 0:
            self.days_left = 6
            return LanternFish()
        else:
            self.days_left -= 1
            return None


def print_fishes(school):
    f = [fish.days_left for fish in school]
    print(f)


def lantern_fish_evolve(data, days):
    school_of_fish = [0 for _ in range(0, 9)]
    for num in data:
        school_of_fish[num] += 1

    tail = 8
    head = 6
    for _ in range(0, days):
        tail = 0 if (tail + 1) == 9 else (tail + 1)
        head = 0 if (head + 1) == 9 else (head + 1)
        school_of_fish[head] += school_of_fish[tail]

    return sum(school_of_fish)


class Day06(Puzzle, year=2021, day=6):
    @staticmethod
    def clean_input(data):
        return list(map(lambda x: int(x), data[0].split(',')))

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return lantern_fish_evolve(self.data, 80)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return lantern_fish_evolve(self.data, 256)
