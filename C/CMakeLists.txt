cmake_minimum_required(VERSION 3.20)

project(aoc_main)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

string(APPEND CMAKE_C_FLAGS_DEBUG " -O0 -ggdb3 -Wall -Wextra")

string(APPEND CMAKE_C_FLAGS_RELWITHDEBINFO " -DNDEBUG")

string(APPEND CMAKE_C_FLAGS_RELEASE " -mavx")
set(CMAKE_C_FLAGS_MEMDEBUG "${CMAKE_C_FLAGS_DEBUG} -DMEMDEBUG")
set(CMAKE_C_FLAGS_DEBUGVERBOSE
    "${CMAKE_C_FLAGS_DEBUG} -ggdb -O0 -DDEBUG_VERBOSE")

set(AOC_YEARS
    2015
    2016
    2017
    2018
    2019
    2020
    2021
    2022
    2023
    2024)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(AocGenerateDays)

add_subdirectory(lib)

foreach(year ${AOC_YEARS})
  message(${CMAKE_SOURCE_DIR}/${year}/CMakeLists.txt)
  if(EXISTS ${CMAKE_SOURCE_DIR}/${year}/CMakeLists.txt)
    message(Found ${year})
    add_subdirectory(${year})
  endif()
endforeach()
