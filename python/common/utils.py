class Helpers:
    @staticmethod
    def minmax(x, y):
        return (min(x, y), max(x, y))

    @staticmethod
    def sign(number):
        return 1 if number > 0 else -1

    @staticmethod
    def manhattan(pos):
        return abs(pos[0]) + abs(pos[1])


def sign(number):
    return 1 if number > 0 else -1
