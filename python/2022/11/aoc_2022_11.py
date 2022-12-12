import sys
from common import timer, Puzzle


class Monkey(object):
    def __init__(self, group: list = None, id=None):
        self.id = id
        self.items = [int(item.strip())
                      for item in group[1].split(":")[1].split(",")]
        self.operation = group[2].split("=")[1].strip()
        self.divisor = int(group[3].split()[-1])
        self.receiver_true = int(group[4][-1])
        self.receiver_false = int(group[5][-1])
        self.inspected_items = 0
        # self.report()

    def perform_operation(self, item):
        parts = self.operation.split()
        if parts[1] == '*':
            if parts[2] == 'old':
                new_item = item * item
            else:
                new_item = item * int(parts[2])
        else:
            if parts[2] == 'old':
                new_item = item + item
            else:
                new_item = item + int(parts[2])
        return new_item

    def throw(self, divisor):
        # If the item list is not empty,
        # do the operation of the first item
        if self.items:
            item = self.items.pop(0)
            return_value = self.perform_operation(item) // divisor
            return return_value

    def receive(self, item):
        self.items.append(item)

    def inspect(self, divisor):
        # check criteria
        # throw to monkey based on criteria
        result = self.throw(divisor)
        self.inspected_items += 1
        if result % self.divisor == 0:
            return (self.receiver_true, result)
        else:
            return (self.receiver_false, result)
        # increase self.inspected_items

    def report(self):
        print(f"Monkey {self.id}")
        print(f"{self.items=}")
        print(f"{self.divisor=}")


class Day11(Puzzle, year=2022, day=11):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.monkeys = list()

        for group in self.data:
            monkey = Monkey(group=group, id=len(self.monkeys))
            self.monkeys.append(monkey)

    @staticmethod
    def clean_input(data):
        return Puzzle.parse_input_groups(data)

    def round(self, divisor):
        monkey: Monkey
        for monkey in self.monkeys:
            while monkey.items:
                receiver, item = monkey.inspect(divisor)
                self.monkeys[receiver].receive(item)

    def solve(self, rounds=20, divisor=3):
        for round in range(rounds):
            self.round(divisor)
            if round % 100 == 0:
                inspected = sorted(
                    [monkey.inspected_items for monkey in self.monkeys]
                )
                monkey_list = [len(monkey.items) for monkey in self.monkeys]
                print(f"{round=}: {inspected}, {monkey_list=}")
        inspected = sorted([monkey.inspected_items for monkey in self.monkeys])

        return inspected[-1]*inspected[-2]

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return self.solve()

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        return self.solve(rounds=10000, divisor=1)


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day11(filename=filename).solve_all()
