#!/usr/bin/env python3
import importlib
import os
import sys
from typing import Any

from common.timer import timer


class AocRunner(object):
    year: str | int

    def __init__(
        self,
        year: str | None = None,
        day: str | None = None,
        exclude: int | None = None,
        filename: str | None = None,
        data: list[Any] | None = None,
        test: bool = False,
    ):
        if year is not None:
            self.year = year
        else:
            self.year = "2023"
        self.days: list[Any] = []
        if day:
            for d in day.split(","):
                if "-" in d:
                    self.days.extend(range(int(d.split("-")[0]), int(d.split("-")[1]) + 1))
                else:
                    self.days.append(int(d))
        self.data: list[Any] | None = None
        if exclude is not None:
            self.exclude_day = [int(exclude)]
        else:
            self.exclude_day = []
        self.filename = None
        if filename is not None:
            self.filename = filename
        else:
            if test:
                self.filename = "test_input.txt"
            elif data is not None:
                self.data = data
                print(f"{self.data=}")

    @timer(part=0, title="Total run time", show_return=False)
    def run(self):
        class_list: Any = self.get_classes()
        result = None
        for year, cls in class_list:
            print(f"Year {year} - {cls.__name__}")
            print("{0:=<60}".format(""))
            try:
                result = cls(filename=self.filename, data=self.data).solve_all()
            except ModuleNotFoundError:
                print("Unable to import submodule")
            print("{0:=<60}".format(""))
            print("")

        return result

    def get_classes(self) -> list[Any]:
        class_list: list[Any] = list()
        if self.days:
            days = self.days
        else:
            days = range(1, 26)

        if self.year is not None:
            year_list = [int(self.year)]
        else:
            year_list = range(2015, 2024)

        for year in year_list:
            for day in days:
                if day in self.exclude_day:
                    continue
                module = f"aoc_{year}_{day:02d}"
                source_path = os.path.join(f"y{year}", f"d{day:02d}")
                source_file = os.path.join(source_path, f"{module}.py")
                if os.path.exists(source_file):
                    try:
                        sys.path.append(source_path)
                        puzzle = importlib.import_module(f"y{year}.d{day:02d}.{module}")
                        try:
                            class_in_module = getattr(puzzle, f"Day{day:02d}")
                            class_list.append((year, class_in_module))
                        except AttributeError as e:
                            print(e)
                            print(f"No solution for day {day:02d} for {year}")
                    except ModuleNotFoundError:
                        print(f"Unable to import submodule for {year} - {day}")
                    finally:
                        sys.path.remove(source_path)
                else:
                    print(f"{source_file=} not found")
        return class_list
