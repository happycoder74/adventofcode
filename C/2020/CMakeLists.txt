aoc_generate_year_light(2020)

target_sources(
  aoc_2020_07
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_array.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_string.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_utils.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_io.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_list.c
  PRIVATE ${CMAKE_SOURCE_DIR}/lib/aoc_hash.c)
target_include_directories(aoc_2020_07 PRIVATE ${GLIB_INCLUDE_DIRS})
target_include_directories(aoc_2020_07 PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(aoc_2020_07 ${GLIB_LDFLAGS})
target_link_libraries(aoc_2020_07 ${CURL_LDFLAGS})
