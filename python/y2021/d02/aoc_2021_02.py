from common import timer, Puzzle


class Day02(Puzzle, year=2021, day=2):
    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        commands = dict(
            forward=0,
            down=0,
            up=0)
        for line in self.data:
            parts = line.split()
            commands[parts[0]] += int(parts[1])

        return commands["forward"] * (commands["down"] - commands["up"])

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        horizontal = 0
        aim = 0
        depth = 0
        for line in self.data:
            parts = line.split()
            if parts[0] == 'forward':
                horizontal += int(parts[1])
                depth += aim*int(parts[1])
            if parts[0] == 'down':
                aim += int(parts[1])
            if parts[0] == 'up':
                aim -= int(parts[1])

        return horizontal * depth
