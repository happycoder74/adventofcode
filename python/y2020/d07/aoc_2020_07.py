import re
from common import timer, Puzzle


class Day07(Puzzle, year=2020, day=7):
    @staticmethod
    def clean_input(data):
        return data

    def find_parent(self, bag, bags, bag_set):
        for color, contents in bags.items():
            for content in contents:
                if bag in content:
                    bag_set.add(self.find_parent(color, bags, bag_set))
        return bag

    def lookup_bags(self, k, bags):
        sum_bags = 0
        for bag, bag_count in bags[k].items():
            sum_bags += bag_count * self.lookup_bags(bag, bags)

        return sum_bags + 1

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        data = [
            line.replace("bags", "bag").replace("bag", "").replace(".", "")
            for line in self.data
        ]
        bags = dict()
        for line in data:
            line_split = line.split("contain")
            key = line_split[0].strip()
            bags[key] = [bag.strip() for bag in line_split[1].split(",")]

        bag_set = set()
        self.find_parent("shiny gold", bags, bag_set)
        return len(bag_set)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        bags = dict()
        for line in self.data:
            content = re.findall(r"(\d+ )?(\w+ \w+) bags?", line)
            bags.update(
                {
                    content[0][1]: {
                        c[1]: int(c[0])
                        for c in content[1:]
                        if c[1] != "no other"
                    }
                }
            )

        return self.lookup_bags("shiny gold", bags) - 1
