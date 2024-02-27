from common import timer, Puzzle


class Day01(Puzzle, year=2023, day=1):
    @staticmethod
    def clean_input(data):
        return data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        sum = 0
        for item in self.data:
           found = [int(c) for c in item if c.isdigit()]
           sum += found[0]*10 + found[-1]
        return sum

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        result = 0
        numbers = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
        for item in self.data:
            p = list()
            p += [(item.find(f), numbers.index(f)) for f in numbers if f in item]
            p += [(item.find(str(i)), i) for i in range(0, 10) if str(i) in item]
            p += [(item.rfind(f), numbers.index(f)) for f in numbers if f in item]
            p += [(item.rfind(str(i)), i) for i in range(0, 10) if str(i) in item]
            found = sorted(p)
            result += found[0][1]*10 + found[-1][1]
        return result
