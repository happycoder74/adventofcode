from common import timer, Puzzle


class Day03(Puzzle, year=2020, day=3):
    def clean_input(self, data):
        return [val for val in data]

    def find_matches(self, slope):
        """ Count number of trees hit using right 3, down 1 """
        col = 0
        row = 0
        matches = 0
        while((row < len(self.data)) & (col < len(self.data[0]))):
            col += slope[0]
            if (col) >= len(self.data[0]):
                col -= len(self.data[0])
            row += slope[1]
            if row >= len(self.data):
                return matches
            if self.data[row][col] == "#":
                matches += 1
        return matches

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        col = 0
        row = 0
        matches = 0
        while((row < len(self.data) - 1) & (col < len(self.data[0]))):
            col += 3
            if (col) >= len(self.data[0]):
                col -= len(self.data[0])
            row += 1
            if self.data[row][col] == "#":
                matches += 1
        return matches

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        slopes = [
            [1, 1],
            [3, 1],
            [5, 1],
            [7, 1],
            [1, 2]
        ]

        number_of_matches = []
        for slope in slopes:
            number_of_matches.append(self.find_matches(slope))
        product = number_of_matches[0]
        for match in number_of_matches[1:]:
            product *= match

        return product
