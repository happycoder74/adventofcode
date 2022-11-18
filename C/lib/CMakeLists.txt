add_library(aoc STATIC aoc_utils.c aoc_timer.c aoc_grid.c)
include_directories(
    ../include
    ${GLIB_INCLUDE_DIRS}
    )
