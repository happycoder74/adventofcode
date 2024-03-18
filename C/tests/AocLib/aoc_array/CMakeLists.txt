add_library(aoc_array
    OBJECT
    check_array.c
    check_test_aoc_int32_array.c
    check_test_aoc_int64_array.c
    check_test_aoc_ptr_array.c
    check_test_aoc_double_array.c
    check_test_aoc_str_array.c
    )

target_include_directories(
    aoc_array
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CHECKLIB_INCLUDE_DIRS}
    PRIVATE $ENV{HOME}/projects/adventofcode-c/C/include
)

