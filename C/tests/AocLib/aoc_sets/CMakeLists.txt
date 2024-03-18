add_library(aoc_sets
  OBJECT
  check_sets.c
  check_test_aoc_sets_int32.c
  )

target_include_directories(
  aoc_sets
  PRIVATE ${CHECKLIB_INCLUDE_DIRS}
  PUBLIC $ENV{HOME}/projects/adventofcode-c/C/include
  )

