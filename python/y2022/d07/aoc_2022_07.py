import sys
from common import timer, Puzzle


class Day7(Puzzle, year=2022, day=7):
    def __init__(self, filename=None, data=None):
        super().__init__(filename=filename, data=data)
        self.root = {}
        self.directories = []
        self.file_system()

    def file_system(self):
        self.add_directory("/")
        for row in self.data:
            row_split = row.split()
            if row.startswith("$ cd"):
                if row_split[-1] == "/":
                    self.directories = ['/']
                elif row_split[-1] == "..":
                    self.directories.pop()
                else:
                    self.directories.append(row_split[-1])
            if row.startswith("dir"):
                self.add_directory(row_split[-1])
            elif row_split[0].isnumeric():
                self.add_file(row_split[1], int(row_split[0]))

    def add_directory(self, directory):
        self.root[tuple(self.directories + [directory])] = {
            'files': list(),
            'size': 0
        }

    def add_file(self, file_name, size):
        self.root[tuple(self.directories)]['files'].append((file_name, size))
        for i in range(len(self.directories)):
            path = tuple(self.directories[:i+1])
            self.root[path]['size'] += size

    @staticmethod
    def clean_input(data):
        return data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        return sum(
            subdir['size'] for subdir in self.root.values()
            if subdir['size'] <= 100000
        )

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        needed_space = 30_000_000
        total_space = 70_000_000
        delete_space = (needed_space -
                        (total_space - self.root[("/", )]['size']))

        return (min(subdir['size'] for subdir in self.root.values()
                    if subdir['size'] >= delete_space))


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day7(filename=filename).solve_all()
