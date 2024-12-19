import argparse
import contextlib
import functools
import math
import os
import statistics

from runner import AocRunner


class Benchmark(object):
    def __init__(self, year: str = "2015", day: str = "1", iterations=10):
        self.year = year
        self.day = day
        self.iterations = int(iterations) if iterations is not None else 10
        self.results = list()

    def run(self):
        runner = AocRunner(self.year, self.day, None, None, None, False)

        with contextlib.redirect_stdout(open(os.devnull, "w")):
            for _ in range(self.iterations):
                result = runner.run()
                self.results.append(result)

        return self.results

    def format_time(self, timing) -> str:
        if timing != 0:
            exponent = math.floor(math.log10(timing) - 1) // -3
            match (exponent):
                case 1:
                    unit = "ms"
                case 2:
                    unit = "\u00B5s"
                case 3:
                    unit = "ns"
                case _:
                    return f"{timing:6.3f} s "

            return f"{timing / (10**(-3 * (exponent))):6.3f} {unit}"
        return f"{timing:.3f} s "

    def report(self, suppress_output=False) -> dict[str, tuple[float, float]]:
        part_results = [
            [val[0][0][0][1] for val in self.results],
            [val[0][0][1][1] for val in self.results],
        ]

        average_time = (
            sum(part_results[0]) / self.iterations,
            sum(part_results[1]) / self.iterations,
        )
        max_time = (
            functools.reduce(max, part_results[0], 0),
            functools.reduce(max, part_results[1], 0),
        )

        min_time = (
            functools.reduce(min, part_results[0], 1000000),
            functools.reduce(min, part_results[1], 1000000),
        )

        stddev = (statistics.pstdev(part_results[0]), statistics.pstdev(part_results[1]))

        if not suppress_output:
            print(f"Benchmark for {self.year} day {self.day} - {self.iterations} iterations")
            for part in range(2):
                print(
                    ", ".join(
                        [
                            f"Part {part+1}: Min: {self.format_time(min_time[part])}",
                            f"Max: {self.format_time(max_time[part])}",
                            f"Average: {self.format_time(average_time[part])}",
                            f"Std Dev.: {self.format_time(stddev[part])}",
                        ]
                    )
                )

        return {"max": max_time, "min": min_time, "average": average_time}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="bench.py", description="Benchmark Advent of Code solutions"
    )
    parser.add_argument("-y", "--year", help="Year to be run")
    parser.add_argument("-d", "--day", help="Day to be run")
    parser.add_argument("-n", "--iterations", help="Iterations per benchmark")

    args = parser.parse_args()

    bench = Benchmark(year=args.year, day=args.day, iterations=args.iterations)
    results = bench.run()
    bench.report()
