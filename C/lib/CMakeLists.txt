set(AOC_LIB_SOURCES
	${CMAKE_SOURCE_DIR}/lib/aoc_utils.c
	${CMAKE_SOURCE_DIR}/lib/aoc_string.c
	${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
	${CMAKE_SOURCE_DIR}/lib/aoc_hash.c
	${CMAKE_SOURCE_DIR}/lib/aoc_list.c
	${CMAKE_SOURCE_DIR}/lib/aoc_array.c
)

add_library(aoc
	${AOC_LIB_SOURCES}
	)

target_include_directories(aoc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(aoc PRIVATE ${GLIB_INCLUDE_DIRS})
target_compile_options(aoc PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wno-error=unused -Wno-error=unused-parameter
	)

