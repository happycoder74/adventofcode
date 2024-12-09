from common import Puzzle, timer


class Day05(Puzzle, year=2024, day=5):
    @staticmethod
    def clean_input(data) -> tuple[list[str], list[str]]:
        rules = []
        updates = []
        for line in data:
            if "|" in line:
                node, target = line.split("|")
                rules.append((node, target))
            elif line != "":
                updates.append(line.split(","))

        return (rules, updates)

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        result = 0
        links = dict()

        for node, target in self.data[0]:
            targets = links.setdefault(node, [])
            targets.append(target)

        for update in self.data[1]:
            right_order = True
            for index in range(len(update)):
                node = update[index]
                if node not in links.keys():
                    continue

                for target in update[index + 1 :]:
                    if target not in links[node]:
                        right_order = False
                        break
                for target in update[:index]:
                    if target in links[node]:
                        right_order = False
                        break
                if not right_order:
                    break
            if right_order:
                result += int(update[int(len(update) / 2)])

        return result

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        result = 0

        return result
