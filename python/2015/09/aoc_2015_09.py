import sys
from itertools import permutations
from common import timer, get_input


def clean_input(data):
    return_data = []
    for line in data:
        split_line = line.split()
        return_data.append([split_line[0], split_line[2], split_line[-1]])

    return return_data


def get_distances(data):
    cities = dict()
    for city in data:
        if city[0] not in cities.keys():
            cities[city[0]] = {city[1]: int(city[2])}
        else:
            cities[city[0]].update({city[1]: int(city[2])})
        if city[1] not in cities.keys():
            cities[city[1]] = {city[0]: int(city[2])}
        else:
            cities[city[1]].update({city[0]: int(city[2])})

    return cities


def calc_routes(cities):
    routes = []
    for route in list(permutations(cities.keys())):
        length = 0
        for i in range(len(route) - 1):
            length += cities[route[i]][route[i + 1]]
        routes.append(length)

    return routes


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    cities = get_distances(data)
    routes = calc_routes(cities)

    return min(routes)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    cities = get_distances(data)
    routes = calc_routes(cities)

    return max(routes)


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2015, 9))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
