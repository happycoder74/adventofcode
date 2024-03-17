add_library(aoc_sets
  OBJECT
  check_sets.c
  check_test_aoc_sets_int32.c
  )

target_include_directories(
  aoc_sets
  PUBLIC $ENV{HOME}/projects/adventofcode-c/C/include
  )

