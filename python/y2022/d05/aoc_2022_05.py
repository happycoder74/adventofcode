import copy
from common import timer, Puzzle


class Day05(Puzzle, year=2022, day=5, stripped=False):

    @staticmethod
    def clean_input(data):
        stacks_read = False
        for index, row in enumerate(data):
            if row.split()[0] == "1":
                nstacks = int(row.split()[-1])
                stacks = [list() for n in range(nstacks)]
                for layer in data[index - 1::-1]:
                    crates = layer[1::4]
                    for stack, crate in enumerate(crates):
                        if crate != ' ':
                            stacks[stack].append(crate)

                stacks_read = True
            if stacks_read:
                break
        instructions = list()
        for row in data[index + 2:]:
            parts = row.split()
            instructions.append((int(parts[1]),
                                 int(parts[3])- 1,
                                 int(parts[5]) - 1))

        return (stacks, instructions)

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        stacks, instructions = self.data
        stacks = copy.deepcopy(stacks)

        for instruction in instructions:
            crates = stacks[instruction[1]][-instruction[0]:]
            stacks[instruction[1]] = stacks[instruction[1]][:-instruction[0]]
            stacks[instruction[2]] += crates[::-1]

        message = ''
        for stack in stacks:
            if len(stack) > 0:
                message += stack[-1]
        return message

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        stacks, instructions = self.data

        for number, _from, to in instructions:
            crates = stacks[_from][-number:]
            stacks[_from] = stacks[_from][:-number]
            stacks[to] += crates

        message = ''
        for stack in stacks:
            if len(stack) > 0:
                message += stack[-1]
        return message
