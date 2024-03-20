add_library(aoc)

target_sources(
    aoc
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_array.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_grid.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_hash.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_io.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_list.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_regex.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_sets.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_stack.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_string.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_alloc.c
    PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_utils.c
)

target_include_directories(aoc
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${GLIB_INCLUDE_DIRS}
    PRIVATE ${CURL_INCLUDE_DIR}
    PRIVATE ${PCRE2POSIX_INCLUDE_DIR}
)
target_link_libraries(aoc
    PRIVATE ${GLIB_LIBRARIES}
    PRIVATE ${CURL_LIBRARIES}
    PRIVATE ${PCRE2POSIX_LIBRARIES}
)

