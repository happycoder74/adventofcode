add_library(aoc_string
    OBJECT
    check_aoc_string.c
    check_test_aoc_string.c
    )

target_include_directories(
    aoc_string
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CHECKLIB_INCLUDE_DIRS}
    PRIVATE $ENV{HOME}/projects/adventofcode-c/C/include
)


