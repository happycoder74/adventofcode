#!/usr/bin/env python3
import argparse

from common import AocRunner

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="runner.py", description="Run Advent of Code solutions")
    parser.add_argument("filename", nargs="?", help="Filename to be used")
    parser.add_argument("--test", help="Run test case", action="store_true")
    parser.add_argument("-y", "--year", help="Year to be run")
    parser.add_argument("-d", "--day", help="Day to be run")
    parser.add_argument("-x", "--exclude_day", help="Exclude day from run")
    parser.add_argument("--data", help="Direct input of data")

    args = parser.parse_args()
    data = args.data.split(",") if args.data else None

    runner = AocRunner(
        year=args.year,
        day=args.day,
        exclude=args.exclude_day,
        filename=args.filename,
        data=data,
        test=args.test,
    )
    runner.run()
