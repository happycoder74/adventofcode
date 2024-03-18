add_library(
  aoc_hash
  OBJECT
  check_aoc_hash.c
  check_test_aoc_hash_table_from_glib.c
  check_test_aoc_hash_table_generic_buckets.c
  check_test_aoc_hash_table_generic_contains.c
  check_test_aoc_hash_table_generic_char.c
  check_test_aoc_hash_table_generic_int32.c
  check_test_aoc_hash_table_generic_point.c
  )

target_include_directories(
    aoc_hash
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${CHECKLIB_INCLUDE_DIRS}
    PRIVATE $ENV{HOME}/projects/adventofcode-c/C/include
)

