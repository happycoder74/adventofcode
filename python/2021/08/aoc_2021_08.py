import sys
from common import timer, get_input


def clean_input(data):
    return_data = [d.split("|") for d in data]
    return_data = [
        (d[0].strip().split(), d[1].strip().split()) for d in return_data
    ]
    return return_data


def decode_signal(signal):
    signal.sort(key=len)
    signal_set_key = {1: 0, 7: 1, 4: 2, 8: 9}

    signal_sets = []
    for part in signal:
        signal_sets.append({letter for letter in part})
    for i, part in enumerate(signal_sets):
        if len(part) == 5:
            if len(part.intersection(signal_sets[signal_set_key[1]])) == 2:
                signal_set_key[3] = i
            elif len(part.intersection(signal_sets[signal_set_key[4]])) == 2:
                signal_set_key[2] = i
            else:
                signal_set_key[5] = i
        if len(part) == 6:
            if len(part.difference(signal_sets[signal_set_key[4]])) == 2:
                signal_set_key[9] = i
            elif len(part.difference(signal_sets[signal_set_key[5]])) == 2:
                signal_set_key[0] = i
            else:
                signal_set_key[6] = i

    decoded = dict()
    for key, index in signal_set_key.items():
        decoded[key] = signal_sets[index]

    return decoded


def decode(keys, signal):
    message = []
    signal_sets = [{letter for letter in part} for part in signal]
    for s in signal_sets:
        for key, val in keys.items():
            if val == s:
                message.append(key)
    return message


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    count = 0
    for item in data:
        for d in item[1]:
            if len(d) in [2, 3, 4, 7]:
                count += 1
    return count


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    output = []
    for item in data:
        decoded = decode_signal(item[0])
        message = decode(decoded, item[1])
        output.append(
            sum([a * b for a, b in zip(message, [1000, 100, 10, 1])])
        )

    return sum(output)


@timer(part="main", title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 8))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
