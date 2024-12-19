import contextlib
import functools
import math
import os
import sys

from runner import AocRunner


def format_time(timing) -> str:
    if timing != 0:
        exponent = math.floor(math.log10(timing) - 1) // -3
        match (exponent):
            case 1:
                unit = "ms"
            case 2:
                unit = "us"
            case 3:
                unit = "ns"
            case _:
                return f"{timing:6.3f} s "

        return f"{timing / (10**(-3 * (exponent))):6.3f} {unit}"

    return f"NOPE {timing:.3f} s "


runner = AocRunner("2024", "10", None, None, None, False)
results = list()

with contextlib.redirect_stdout(open(os.devnull, "w")):
    for i in range(10):
        result = runner.run()
        results.append(result)


max_time = (
    functools.reduce(max, [val[0][0][0][1] for val in results], 0),
    functools.reduce(max, [val[0][0][1][1] for val in results], 0),
)

min_time = (
    functools.reduce(min, [val[0][0][0][1] for val in results], 1000000),
    functools.reduce(min, [val[0][0][1][1] for val in results], 1000000),
)

for part in range(2):
    print(f"Part {part+1}: Min: {format_time(min_time[part])} Max: {format_time(max_time[part])}")
