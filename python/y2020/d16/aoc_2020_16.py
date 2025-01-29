import functools

from common import Puzzle, timer


def count_bits(n: int) -> int:
    count = 0
    while n:
        count += n & 1
        n >>= 1
    return count


def find_bit(n: int) -> int:
    for i in range(0, 20):
        if (n >> i) & 1 == 1:
            return i
    return -1


class Day16(Puzzle, year=2020, day=16):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.classes = self.get_classes()
        self.my_ticket = self.get_my_ticket()
        self.tickets = self.get_tickets()

    @staticmethod
    def clean_input(data: list[str]) -> list:
        groups = list()
        group = list()
        for row in data:
            if row == "":
                groups.append(group)
                group = list()
            else:
                group.append(row)
        groups.append(group)
        return groups

    def get_classes(self) -> dict[str, list[tuple[int, int]]]:
        rows = self.data[0]

        d = dict()
        for row in rows:
            name, numbers = row.split(":")
            d[name] = [(int(v.split("-")[0]), int(v.split("-")[1])) for v in numbers.split(" or ")]

        return d

    def get_my_ticket(self):
        d = self.data[1][1]
        return [int(v) for v in d.split(",")]

    def get_tickets(self):
        tickets = [[int(v) for v in d.split(",")] for d in self.data[2][1:]]
        return tickets

    def in_range(self, n: int, r: list[tuple[int, int]]) -> bool:
        return any([rr[0] <= n <= rr[1] for rr in r])

    def is_valid(self, ticket: list[int], classes: dict[str, list[tuple[int, int]]]) -> bool:
        ranges = [v for v in classes.values()]
        return all([any([self.in_range(n, class_range) for class_range in ranges]) for n in ticket])

    def check_range(self, tickets: list[list[int]], row: list[tuple[int, int]]) -> list[list[int]]:
        check_rows = list()
        for ticket in tickets:
            check_row = [0] * len(ticket)
            for i, v in enumerate(ticket):
                if any([r[0] <= v <= r[1] for r in row]):
                    check_row[i] = 1
            check_rows.append(check_row)
        return check_rows

    def compute_masks(self) -> dict[str, list[int]]:
        d = self.classes
        valid_tickets = self.tickets

        checks = dict()
        masks = dict()
        for name, ranges in d.items():
            checks[name] = self.check_range(valid_tickets, ranges)
            masks[name] = [int("".join([str(v) for v in l]), 2) for l in checks[name]]
        return masks

    @timer(part=1)
    def solve_part_1(self) -> int:
        errors = 0
        valid = list()
        for ticket in self.tickets:
            for number in ticket:
                if not any(self.in_range(number, r) for r in self.classes.values()):
                    errors += number
                    break
            else:
                valid.append(ticket)
        self.tickets = valid
        return errors

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        positions = dict()
        masks = self.compute_masks()
        result: dict[str, tuple[int, int]] = {
            name: (i, functools.reduce(lambda x, y: x & y, m))
            for i, (name, m) in enumerate(masks.items())
        }
        sorted_result: list[tuple[str, tuple[int, int]]] = sorted(
            result.items(), key=lambda x: x[1][1], reverse=True
        )
        while sorted_result:
            item = sorted_result.pop()
            if count_bits(item[1][1]) == 1:
                bit_index = find_bit(item[1][1])
                positions[item[0]] = 19 - bit_index
                for i, v in enumerate(sorted_result):
                    sorted_result[i] = (v[0], (v[1][0], v[1][1] & ~item[1][1]))

        product = 1
        for k, v in positions.items():
            if k.startswith("departure"):
                product *= self.my_ticket[v]
        return product
