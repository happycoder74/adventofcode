import os


class Parser(object):
    def __init__(self, year, day, filename="input.txt", data_directory=None):
        if not data_directory:
            data_directory = f"../../data/{year}/{day}"

        path = os.path.join(
            os.path.dirname(__file__), data_directory
        )
        filename = os.path.join(path, filename)
        self.data = self.get_input(filename)

    def get_input(self, filename):
        print(filename)
        with open(filename) as fp:
            data = fp.read().strip().splitlines()
        return data

    def clean_input(self, data, inplace=False):
        if inplace:
            self.data = data
        else:
            return data
