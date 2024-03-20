add_library(aoc_regex
    OBJECT
    check_aoc_regex.c
    check_test_aoc_regex_count.c
    check_test_aoc_regex_split.c
    )

target_include_directories(
    aoc_regex
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CHECKLIB_INCLUDE_DIRS}
    PRIVATE $ENV{HOME}/projects/adventofcode-c/C/include
)

target_link_libraries(
    aoc_regex
    pcre2-posix
)

