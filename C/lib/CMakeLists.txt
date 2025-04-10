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
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_bench.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_alloc.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_header.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_utils.c)

target_include_directories(
  aoc
  PRIVATE ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CURL_INCLUDE_DIR}
  PRIVATE ${PCRE2POSIX_INCLUDE_DIR})
target_link_libraries(
  aoc
  PRIVATE ${CURL_LIBRARIES}
  PRIVATE ${PCRE2POSIX_LIBRARIES})

add_library(aoclight)

target_sources(
  aoclight
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_header.c)

target_include_directories(aoclight PRIVATE ${CMAKE_SOURCE_DIR}/include)
