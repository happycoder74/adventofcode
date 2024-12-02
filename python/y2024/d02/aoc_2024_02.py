from common import Puzzle, timer


class Day02(Puzzle, year=2024, day=2):
    @staticmethod
    def clean_input(data: list[str]) -> list[list[int]]:
        cleaned = []
        for row in data:
            cleaned.append([int(v) for v in row.split()])
        return cleaned

    def is_safe(self, row: list[int]) -> bool:
        return_value = all([1 <= abs(v) <= 3 for v in row])
        return_value = return_value and (all([v > 0 for v in row]) or all([v < 0 for v in row]))
        return return_value

    @timer(part=1)
    def solve_part_1(self) -> int:
        """Solution for part 1"""
        safe_count = 0
        for row in self.data:
            checklist = [(a - b) for a, b in zip(row[:-1], row[1:])]
            if self.is_safe(checklist):
                safe_count += 1

        return safe_count

    def check_row(self, row: list[int]) -> bool:
        checklist = [(a - b) for a, b in zip(row[:-1], row[1:])]
        return self.is_safe(checklist)

    @timer(part=2)
    def solve_part_2(self) -> int:
        """Solution for part 2"""
        safe_count = 0
        for row in self.data:
            if self.check_row(row):
                safe_count += 1
            else:
                for i in range(len(row)):
                    if self.check_row(row[:i] + row[i + 1 :]):
                        safe_count += 1
                        break

        return safe_count
