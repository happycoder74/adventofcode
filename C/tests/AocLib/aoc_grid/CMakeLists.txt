add_library(aoc_grid
    OBJECT
    check_aoc_grid.c
    check_test_aoc_grid_int32.c
    )

target_include_directories(
    aoc_grid
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CHECKLIB_INCLUDE_DIRS}
    PRIVATE $ENV{HOME}/projects/adventofcode-c/C/include
)


