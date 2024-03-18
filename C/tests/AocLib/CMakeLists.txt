cmake_minimum_required(VERSION 3.20)

project(aoc_lib_test)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

string(APPEND CMAKE_C_FLAGS_DEBUG " -O0 -ggdb3 -Wall -Wextra")
find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

find_package(PkgConfig REQUIRED)
pkg_search_module(CHECKLIB REQUIRED check)


find_library(
  AOC_LIB
  aoc
  PATHS $ENV{HOME}/projects/adventofcode-c/C/debug/lib
  )

add_subdirectory(aoc_sets)
add_subdirectory(aoc_array)
add_subdirectory(aoc_hash)
add_subdirectory(aoc_grid)
add_subdirectory(aoc_string)
add_subdirectory(aoc_stack)

add_executable(aoc_lib_test
  check_aoclib.c
  $<TARGET_OBJECTS:aoc_sets>
  $<TARGET_OBJECTS:aoc_array>
  $<TARGET_OBJECTS:aoc_hash>
  $<TARGET_OBJECTS:aoc_grid>
  $<TARGET_OBJECTS:aoc_string>
  $<TARGET_OBJECTS:aoc_stack>
  )

target_include_directories(
  aoc_lib_test
  PUBLIC ${CHECKLIB_INCLUDE_DIRS}
  )

target_link_libraries(
    aoc_lib_test
    ${GLIB_LDFLAGS}
    ${CHECKLIB_LDFLAGS}
)
target_link_libraries(aoc_lib_test
  ${AOC_LIB}
  glib-2.0
  curl
  ${CHECK_LIBRARIES}
  ${CHECKLIB_LIBRARIES}
  pthread
  m
  )

add_custom_target(
  run_tests
  COMMAND aoc_lib_test
  DEPENDS aoc_lib_test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )

message("CHECKLIB_LDFLAGS = " ${CHECKLIB_LDFLAGS})
