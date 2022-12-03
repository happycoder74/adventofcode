# Advent of Code in C

Stepping up the game a notch for me! After finding the Advent of Code and running the 2021 challenge in Python I am now trying to solve the problems using C, my old go-to language which has not been used a lot lately. 

Due to some laziness I am utilizing GLib at least to start with. My goal is to finish the puzzles using plain old C and the functions provided by the standard library. Let's see how it goes :-)

A messy Makefile is included which allows to run or test the solutions from the adventofcode/C direcory using the command:

```make run YEAR=<year> DAY=<day>``` or ```make test YEAR=<year> DAY=<day>```

or to just build the solution:

```make YEAR=<year> DAY=<day>```

where `<year>` is pretty self explanatory and `<day>` is the number of the day (with leading zero for day 1 to 9, e.g `01`, `02` etc).

## 2022:
| Day | Stars            | Timing Part 1 | Timing Part 2 |
|:---:|:-----------------|--------------:|--------------:|
|  1  | &#11088;&#11088; | 0.029 ms      | 0.009 ms      |
