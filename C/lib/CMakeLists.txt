
add_library(aoc)

target_sources(
    aoc
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_utils.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_string.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_hash.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_list.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_array.c
    )

target_include_directories(aoc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(aoc PRIVATE ${GLIB_INCLUDE_DIRS})

target_compile_options(aoc PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wno-error=unused -Wno-error=unused-parameter
	)

