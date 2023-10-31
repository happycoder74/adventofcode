
add_library(aoc
	${AOC_LIB_SOURCES}
    aoc_io.c
	)
target_include_directories(aoc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(aoc PRIVATE ${GLIB_INCLUDE_DIRS})
target_compile_options(aoc PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wno-error=unused -Wno-error=unused-parameter
	)

