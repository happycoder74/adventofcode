import argparse

from common import Benchmark

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="bench.py", description="Benchmark Advent of Code solutions"
    )
    parser.add_argument("-y", "--year", help="Year to be run")
    parser.add_argument("-d", "--day", help="Day to be run")
    parser.add_argument("-n", "--iterations", help="Iterations per benchmark (default 10)")
    parser.add_argument("-b", "--bins", help="Number of histogram bins (default 10)")
    parser.add_argument("-m", "--solution-time", help="Max time per solution in seconds")
    parser.add_argument("-x", "--benchmark-time", help="Max time for benchmark run in seconds")

    args = parser.parse_args()

    bench = Benchmark(
        year=args.year,
        day=args.day,
        iterations=args.iterations,
        bins=args.bins,
        max_solution_time=args.solution_time,
        max_benchmark_time=args.benchmark_time,
    )
    results = bench.run()

    bench.report()
