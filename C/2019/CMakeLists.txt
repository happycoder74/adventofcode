
AOC_GENERATE_YEAR(2019)
target_link_libraries(aoc_2019_02 intcode)
target_include_directories(aoc_2019_02 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/intcode)
add_subdirectory(intcode)

