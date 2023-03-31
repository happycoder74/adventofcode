# Advent of Code in C

[![CMake](https://github.com/happycoder74/adventofcode/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/happycoder74/adventofcode/actions/workflows/cmake.yml)

Stepping up the game a notch for me! After finding the Advent of Code and running the 2021 challenge in Python I am now trying to solve the problems using C, my old go-to language which has not been used a lot lately. 

Due to some laziness I am utilizing GLib at least to start with. My goal is to finish the puzzles using plain old C and the functions provided by the standard library. Let's see how it goes :-)

Possible to build using CMake. Builds with pre-defined custom targets for each day. 
To build run
```cmake -B build .```

To run a specific day, for example Day 1 2021 run:
```cd build
make run_2021_01
```

Or to run a specific year, for example 2021, run:
```
cd build
make run_2021
```

Replace ```make``` above with whatever build system you choose to use in CMake

## 2022:
| Day | Stars            | Timing Part 1 | Timing Part 2 |
|:---:|:-----------------|--------------:|--------------:|
|  1  | &#11088;&#11088; | 0.029 ms      | 0.009 ms      |
|  2  | &#11088;&#11088; | 0.004 ms      | 0.027 ms      |
|  3  |                  |               |               |
|  4  |                  |               |               |
|  5  |                  |               |               |
|  6  | &#11088;&#11088; | 0.371 ms      | 0.678 ms      |
