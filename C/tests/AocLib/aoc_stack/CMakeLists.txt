add_library(aoc_stack
    OBJECT
    check_aoc_stack.c
    check_test_aoc_stack.c
    )

target_include_directories(
    aoc_stack
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CHECKLIB_INCLUDE_DIRS}
    PRIVATE $ENV{HOME}/projects/adventofcode-c/C/include
)



