cmake_minimum_required(VERSION 3.25)
project(aoc++)
add_library(aoc++ 
	aoc_io.cpp
	${CMAKE_SOURCE_DIR}/../include/aoc_io.hpp
	${CMAKE_SOURCE_DIR}/../include/aoc_timer.hpp
)
target_include_directories(aoc++
	PUBLIC
	${CMAKE_SOURCE_DIR}/../include)

