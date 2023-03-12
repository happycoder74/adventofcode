import math
from common import timer, Puzzle


class Day25(Puzzle, year=2022, day=25):
    @staticmethod
    def clean_input(data):
        return data

    def decode(self, num_str: str, verbose: int = 1):
        decoded: int = 0
        lookup = {'=': -2, '-': -1, '0': 0, '1': 1, '2': 2}
        decoded = sum(lookup[d]*5**i for i, d in enumerate(num_str[::-1]))
        return decoded

    def encode(self, num: int) -> str:
        mod: int
        encoded: list = []
        lookup = {-2: '=', -1: '-', 0: '0', 1: '1', 2: '2'}
        while num:
            num, mod = divmod(num, 5)
            if mod > 2:
                mod -= 5
                num += 1
            encoded.append(lookup[mod])
        return ''.join(encoded[::-1])

    def encode2(self, num: int) -> str:
        num_digits: int = math.ceil(math.log(2*num) / math.log(5))
        lookup = {-2: '=', -1: '-', 0: '0', 1: '1', 2: '2'}
        snafu_number = []
        for i in range(num_digits - 1, -1, -1):
            digit_value = round(num / (5 ** i))
            num -= digit_value * 5 ** i
            snafu_number.append(lookup[digit_value])
        return ''.join(snafu_number)

    @timer(part=1)
    def solve_part_1(self):
        """solution for part 1"""
        sum_of_numbers: int = 0
        for i, row in enumerate(self.data):
            sum_of_numbers += self.decode(row, verbose=i)
        return self.encode(sum_of_numbers)

    @timer(part=1, title="Alternate p 1")
    def solve_part_1b(self):
        """solution for part 1"""
        sum_of_numbers: int = 0
        for i, row in enumerate(self.data):
            sum_of_numbers += self.decode(row, verbose=i)
        return self.encode2(sum_of_numbers)

    @timer(part=1, title="Alt 2 p 1")
    def solve_part_1c(self):
        """solution for part 1"""
        sum_of_numbers: int = 0
        encode = '012=-'
        return_string = ""
        for i, row in enumerate(self.data):
            sum_of_numbers += self.decode(row, verbose=i)

        while sum_of_numbers:
            return_string += encode[sum_of_numbers % 5]
            if sum_of_numbers > 2:
                sum_of_numbers += 2
            sum_of_numbers //= 5
        return return_string[::-1]

    @timer(part='main', title="Total elapsed", show_return=False)
    def solve_all(self):
        p1 = self.solve_part_1()
        p1b = self.solve_part_1b()
        p1c = self.solve_part_1c()
        return p1, p1b, p1c
