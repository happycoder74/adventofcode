import math
from common import timer, Puzzle


def trajectory(sp, velocity, target_area):
    target_x = [target_area[0][1], target_area[1][1]]
    target_y = [target_area[0][0], target_area[1][0]]
    hit = False
    outside = False
    np = sp
    dx = velocity[0]
    dy = velocity[1]

    while not hit and not outside:
        np = (np[0] + dx, np[1] + dy)
        if (min(target_x) <= np[0] <= max(target_x)) and (
            min(target_y) <= np[1] <= max(target_y)
        ):
            hit = True

        if (np[0] > max(target_x)) or (np[1] < min(target_y)):
            outside = True

        dy -= 1
        if dx > 0:
            dx -= 1
        elif dx < 0:
            dx += 1
        else:
            dx = 0

    return hit


class Day17(Puzzle, year=2021, day=17):
    @staticmethod
    def clean_input(data):
        data = data[0].split(": ")
        data = data[1].split(", ")
        xdata = data[0][2:].split("..")
        ydata = data[1][2:].split("..")
        data = [(int(ydata[0]), int(xdata[0])), (int(ydata[1]), int(xdata[1]))]
        return data

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        data = self.data
        if (data[0][0] < 0) and (data[1][0] < 0):
            ymin = min(data[0][0], data[1][0])
            return sum(range(abs(ymin + 1) + 1))

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        target_area = self.data
        target_x = [target_area[0][1], target_area[1][1]]
        target_y = [target_area[0][0], target_area[1][0]]
        velocities = []

        min_x = math.ceil((-1 + math.sqrt(1 + 4*min(target_x))) / 2)
        for y in range(min(target_y), abs(min(target_y)) + 1):
            for x in range(min_x, max(target_x) + 1):
                if (trajectory((0, 0), (x, y), target_area)):
                    velocities.append((x, y))

        return len(velocities)
