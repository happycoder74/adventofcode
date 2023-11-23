
add_library(aoc)

target_sources(
    aoc
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_utils.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_string.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_hash.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_list.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_array.c
	PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_io.c
    )

target_include_directories(aoc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(aoc PRIVATE ${GLIB_INCLUDE_DIRS})
find_package(CURL REQUIRED)
target_include_directories(aoc PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(aoc PRIVATE ${CURL_LIBRARIES})

target_compile_options(aoc PRIVATE
    -Wall -Wextra -pedantic -Wno-error=unused -Wno-error=unused-parameter
	)

