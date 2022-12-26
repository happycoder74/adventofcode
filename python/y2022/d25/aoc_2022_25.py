from common import timer, Puzzle


class Day25(Puzzle, year=2022, day=25):
    @staticmethod
    def clean_input(data):
        return data

    def decode(self, num_str: str, verbose: int = 1):
        decoded: int = 0
        lookup = {'=': -2, '-': -1, '0': 0, '1': 1, '2': 2}
        decoded = sum (lookup[d]*5**i for i, d in enumerate(num_str[::-1]))
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

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        sum_of_numbers: int = 0
        for i, row in enumerate(self.data):
            sum_of_numbers += self.decode(row, verbose=i)
        return self.encode(sum_of_numbers)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return None
