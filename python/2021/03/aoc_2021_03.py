import sys
from common import timer, get_input


def clean_input(data):
    return data


def common_value(data, position, method):
    sum = 0
    for bits in data:
        sum += int(bits[position])
    check = sum / len(data)
    if method == 'most':
        return_value = str(int(check < 0.5))
    else:
        return_value = str(int(check >= 0.5))

    return return_value


def reduce_list(data, value, position):
    d = []
    for index, item in enumerate(data):
        if item[position] != value:
            d.append(item)
    return d


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    sum = [0] * len(data[0])
    sum2 = sum.copy()
    for bits in data:
        for i in range(0, len(bits)):
            sum[i] += int(bits[i])

    for i, s in enumerate(sum):
        s = s / len(data)
        sum2[i] = s

    gamma = list(map(lambda x: '1' if x > 0.5 else '0', sum2))
    epsilon = list(map(lambda x: '1' if x < 0.5 else '0', sum2))

    return int(''.join(gamma), 2) * int(''.join(epsilon), 2)


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    data2 = data.copy()

    position = 0
    while (len(data) > 1):
        value = common_value(data, position, method='most')
        data = reduce_list(data, value, position)
        position += 1

    position = 0
    while (len(data2) > 1):
        value = common_value(data2, position, method='least')
        data2 = reduce_list(data2, value, position)
        position += 1

    oxygen_generator_rating = int(''.join(data), 2)
    co2_scrubber_rating = int(''.join(data2), 2)

    return oxygen_generator_rating * co2_scrubber_rating


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 3))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
