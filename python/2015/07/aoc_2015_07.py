import sys
import numpy as np
from common import timer, get_input


def clean_input(data):
    return_data = []
    for line in data:
        oper, dest = line.split(' -> ')
        return_data.append((oper, dest))
    return return_data


@timer(part=1)
def solve_part_1(data_orig, return_key='a', preset=None):
    """ Solution for part 1 """
    result = dict()
    data = data_orig.copy()
    if preset is not None:
        result.update(preset)

    while data:
        oper, dest = data.pop(0)
        if preset and dest in preset.keys():
            continue
        else:
            expression = oper.split()
            if len(expression) == 1:
                if oper.isnumeric():
                    result[dest] = np.uint16(oper)
                else:
                    if oper in result.keys():
                        result[dest] = result[oper]
                    else:
                        data.append([oper, dest])
                        continue
            elif len(expression) == 2:
                op, rop = expression
                if op == 'NOT':
                    if rop.isnumeric():
                        right = np.uint16(rop)
                    elif rop in result.keys():
                        right = result[rop]
                    else:
                        data.append([oper, dest])
                        continue
                    result[dest] = ~right
            else:
                lop, op, rop = expression

                if lop not in result.keys() and not lop.isnumeric():
                    data.append([oper, dest])
                    continue
                if rop not in result.keys() and not rop.isnumeric():
                    data.append([oper, dest])
                    continue

                left = np.uint16(lop) if lop.isnumeric() else result[lop]
                right = np.uint16(rop) if rop.isnumeric() else result[rop]

                if op == 'AND':
                    result[dest] = left & right
                elif op == 'OR':
                    result[dest] = left | right
                elif op == 'LSHIFT':
                    result[dest] = left << right
                elif op == 'RSHIFT':
                    result[dest] = left >> right

    if return_key is None:
        return {key: result[key] for key in sorted(result)}
    else:
        return result[return_key]


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    preset = dict(b=solve_part_1(data))
    return solve_part_1(data, preset=preset)


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2015, 7))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
