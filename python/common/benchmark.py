import contextlib
import functools
import math
import os
import statistics
import sys

import numpy as np
from common.aocrunner import AocRunner
from common.progress_bar import progress_bar


class Benchmark(object):
    def __init__(
        self,
        year: str = "2015",
        day: str = "1",
        iterations=None,
        bins=None,
        max_solution_time=None,
        max_benchmark_time=None,
    ):
        self.year = year
        self.day = day
        self.iterations = int(iterations) if iterations is not None else 10
        self.results = list()
        self.bins = int(bins) if bins is not None else 10
        self.max_solution_time = int(max_solution_time) if max_solution_time is not None else 1
        self.max_benchmark_time = int(max_benchmark_time) if max_benchmark_time is not None else 600

    def run(self):
        self.results = list()
        reduced = False
        reduced_limit = self.iterations
        with contextlib.redirect_stdout(open(os.devnull, "w")):
            for iteration in range(self.iterations):
                if iteration >= reduced_limit:
                    break
                runner = AocRunner(self.year, self.day, None, None, None, False)
                result = runner.run()
                if (not reduced) and (result[0][1] > self.max_solution_time):
                    reduced = True
                    reduced_limit = math.floor(self.max_benchmark_time / result[0][1])
                    print(
                        "Reducing the number of iterations from {} to {} due to long run-time".format(
                            self.iterations, reduced_limit
                        ),
                        file=sys.stderr,
                    )
                if reduced:
                    print(
                        "Iteration {} of {}: {}".format(
                            iteration + 1, reduced_limit, self.format_time(result[0][1])
                        ),
                        file=sys.stderr,
                    )
                self.results.append((result[0][0][0][1], result[0][0][1][1], result[0][1]))
        self.iterations = reduced_limit

        return self.results

    def get_unit(self, exponent):
        match (exponent):
            case 1:
                return "ms"
            case 2:
                return "\u00B5s"
            case 3:
                return "ns"
            case _:
                return "s "

    def format_time(self, timing) -> str:
        if timing != 0:
            exponent = math.floor(math.log10(timing) - 1) // -3
            unit = self.get_unit(exponent)
            return f"{timing / (10**(-3 * (exponent))):6.3f} {unit}"

        return f"{timing:.3f} s "

    def report(self, suppress_output=False) -> dict[str, tuple[float, float]]:
        if not self.results:
            print("No results available")
            return {"empty": (0, 0)}

        part_results = [
            [val[0] for val in self.results],
            [val[1] for val in self.results],
            [val[2] for val in self.results],
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

        stddev = (
            statistics.pstdev(part_results[0]),
            statistics.pstdev(part_results[1]),
        )

        if not suppress_output:
            hist = (
                np.histogram(part_results[0], self.bins),
                np.histogram(part_results[1], self.bins),
            )
            histogram = (hist[0][0], hist[1][0])
            bins = (hist[0][1], hist[1][1])
            exponent = (
                math.floor(math.log10(max_time[0]) - 1) // -3,
                math.floor(math.log10(max_time[1]) - 1) // -3,
            )
            bins_corr = (
                [b / (10 ** (-3 * exponent[0])) for b in bins[0]],
                [b / (10 ** (-3 * exponent[1])) for b in bins[1]],
            )

            report_string = (
                f"Benchmark for {self.year} day {self.day} - {self.iterations} iterations"
            )
            print(report_string)
            print("".join(["="] * len(report_string)))
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
            print()
            print(
                "{:75s} {:75s}".format(
                    "Part 1 ({})".format(self.get_unit(exponent[0])),
                    "Part 2 ({})".format(self.get_unit(exponent[1])),
                )
            )
            for (b1s, b1e, h1), (b2s, b2e, h2) in zip(
                zip(bins_corr[0][:-1], bins_corr[0][1:], histogram[0]),
                zip(bins_corr[1][:-1], bins_corr[1][1:], histogram[1]),
            ):
                bar1 = f"{b1s:7.3f} - {b1e:7.3f}: {progress_bar(h1 / self.iterations, 40)} ({h1 / self.iterations * 100:2.0f} %)"
                bar2 = f"{b2s:7.3f} - {b2e:7.3f}: {progress_bar(h2 / self.iterations, 40)} ({h2 / self.iterations * 100:2.0f} %)"
                print("{:75s} {:75s}".format(bar1, bar2))

        return {"max": max_time, "min": min_time, "average": average_time}
