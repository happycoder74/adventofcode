import re
import string
import sys

from common import timer, Puzzle


class Day11(Puzzle, year=2015, day=11):
    def clean_input(self, data):
        return data[0]

    @timer(part=1)
    def solve_part_1(self):
        self.password = Password(self.data)
        return self.password.solve()

    @timer(part=2)
    def solve_part_2(self):
        self.password.next()
        return self.password.solve()


class Password(object):
    def __init__(self, password: str = "") -> None:
        if len(password) != 8:
            raise Exception(
                f"Password must be 8 characters '{password}' given"
            )
        self.password: list = list(password)
        self.valid_pattern_1 = re.compile(r'(\w)\1.*(\w)\2')
        letters: str = string.ascii_lowercase
        triplets: str = ('|'.join(letters[i:i+3]
                                  for i, v in enumerate(letters[:-2])))
        invalid_triplets = re.findall(r"\|\w*[iol]\w*", triplets)
        for invalid in invalid_triplets:
            triplets = triplets.replace(invalid, "")
        self.valid_pattern_2 = re.compile(triplets)
        self.invalid_pattern = re.compile(r'[ilo]')

    @staticmethod
    def next_letter(letter: str) -> str:
        letters: str = string.ascii_lowercase
        next_index = (letters.index(letter) + 1) % len(letters)
        if (letters[next_index] in ['i', 'o', 'l']):
            next_index += 1
        return letters[next_index]

    def next(self) -> None:
        index: int
        letter: str
        for index, letter in enumerate(reversed(self.password)):
            index_reversed: str = len(self.password) - index - 1
            self.password[index_reversed] = self.next_letter(letter)
            if self.password[index_reversed] != 'a':
                break

    def is_valid(self) -> bool:
        pw: str = ''.join(self.password)
        if not self.valid_pattern_1.search(pw):
            return False
        if not self.valid_pattern_2.search(pw):
            return False
        if self.invalid_pattern.search(pw):
            return False
        return True

    def solve(self) -> str:
        while not self.is_valid():
            self.next()
        return ''.join(self.password)


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day11(filename=filename).solve_all()
