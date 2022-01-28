import os


class Parser(object):
    def __init__(self, year, day, filename="input.txt", data_directory=None):
        if not data_directory:
            data_directory = f"../../data/{year}/{day:02d}"

        path = os.path.join(
            os.path.dirname(__file__), data_directory
        )
        filename = os.path.join(path, filename)
        self.data = self.get_input(filename)

    def get_input(self, filename):
        with open(filename) as fp:
            data = fp.read().strip().splitlines()
        return data

    def clean_input(self, data, inplace=False):
        if inplace:
            self.data = data
        else:
            return data


def get_input(filename, year, day):
    path = os.path.join(os.path.dirname(__file__),
                        f"../../data/{year}/{day:02d}")
    with open(os.path.join(path, filename)) as fp:
        data = fp.read().strip().splitlines()

    return data
