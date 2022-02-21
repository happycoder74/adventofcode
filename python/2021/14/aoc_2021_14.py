import sys
from collections import Counter
from collections import OrderedDict
from common import timer, get_input


def clean_input(data):
    return data


@timer(part=1)
def solve_part_1(data, steps=None):
    """Solution for part 1"""
    template = data[0]
    operations = {p.split(" -> ")[0]: p.split(" -> ")[1] for p in data[2:]}

    if steps is None:
        max_steps = 10
    else:
        max_steps = steps

    for counter in range(0, max_steps):
        new_template = []
        for index, pair in enumerate(template):
            if index < len(template) - 1:
                pair = template[index: index + 2]
                new_part = pair[0] + operations[pair] + pair[1]
                new_template.append(new_part)
        template = new_template[0] + "".join(
            [part[1:] for part in new_template[1:]]
        )

    if steps is not None:
        return template
    template_counter = Counter(template)
    return max(template_counter.values()) - min(template_counter.values())


@timer(part=2)
def solve_part_2(data, steps=None):
    """Solution for part 2"""
    template = data[0]
    operations = {p.split(" -> ")[0]: p.split(" -> ")[1] for p in data[2:]}
    template_dict = OrderedDict()
    #    for key in operations:
    #        template_dict[key] = 0
    sequence_count = Counter(template)

    for i in range(0, len(template) - 1):
        pair = template[i: i + 2]
        if pair in template_dict.keys():
            template_dict[pair] += 1
        else:
            template_dict[pair] = 1

    if steps is None:
        max_steps = 40
    else:
        max_steps = steps

    for step in range(0, max_steps):
        loop_dict = template_dict.copy()
        for key, val in loop_dict.items():
            if val > 0:
                pair1 = key[0] + operations[key]
                pair2 = operations[key] + key[1]
                sequence_count[operations[key]] += val
                for pair in [pair1, pair2]:
                    if pair in template_dict.keys():
                        template_dict[pair] += val
                    else:
                        template_dict[pair] = val
                template_dict[key] -= val
    return max(sequence_count.values()) - min(sequence_count.values())


@timer(part="main", title="Total elapsed", show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 14))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
