import sys
from common import timer, Puzzle


class Day10(Puzzle, year=2022, day=10):
    @staticmethod
    def clean_input(data):
        return_data = list()
        for row in data:
            if row.startswith("a"):
                instr = row.split()
                return_data.extend([instr[0], int(instr[1])])
            elif row == "noop":
                return_data.append(row)
        return return_data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        signal_strengths = list()
        x = 1
        for cycle, instruction in enumerate(self.data, start=1):
            if cycle in [20, 60, 100, 140, 180, 220]:
                signal_strengths.append(cycle * x)
            if isinstance(instruction, int):
                x += int(instruction)
        return sum(signal_strengths)

    def print_crt(self):
        for scanline in range(6):
            line = self.crt[scanline * 40:(scanline + 1)*40]
            print(''.join(line))

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        self.crt = [' ' for _ in range(240)]
        x = 1
        for cycle, instruction in enumerate(self.data):
            sprite_position = [x - 1, x, x + 1]
            if  (cycle % 40) in sprite_position:
                self.crt[cycle] = "\u2591"
            if isinstance(instruction, int):
                x += instruction

        self.print_crt()
        return None


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day10(filename=filename).solve_all()
