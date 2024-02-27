cmake_minimum_required(VERSION 3.22)
project(aoc++)
add_library(aoc++
	aoc_io.cpp
    aoc_string.cpp
)
target_include_directories(aoc++
	PUBLIC
    ${CMAKE_SOURCE_DIR}/include)

