
cmake_minimum_required(VERSION 3.12)
project(aoc_2015_02 C)

set(CMAKE_C_STANDARD 99)

add_executable(aoc_2015_02 aoc_2015_02.c)

include_directories(
    ${PROJECT_SOURCE_DIR}/../../include
    ${GLIB_INCLUDE_DIRS}
    )

target_link_libraries(
    aoc_2015_02
    aoc
    ${GLIB_LIBRARIES}
    )
