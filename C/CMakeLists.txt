cmake_minimum_required(VERSION 3.20)

project(aoc_main)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(AOC_YEARS
	2015 2016 2017 2018 2019 2020 2021 2022
	)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(AocGenerateDays)

set(AOC_LIB_SOURCES
	${CMAKE_SOURCE_DIR}/lib/aoc_utils.c
	${CMAKE_SOURCE_DIR}/lib/aoc_string.c
	${CMAKE_SOURCE_DIR}/lib/aoc_timer.c
	${CMAKE_SOURCE_DIR}/lib/aoc_hash.c
	${CMAKE_SOURCE_DIR}/lib/aoc_list.c
	${CMAKE_SOURCE_DIR}/lib/aoc_array.c
)

add_subdirectory(lib)

foreach (Y ${AOC_YEARS})
	message(${CMAKE_SOURCE_DIR}/${Y}/CMakeLists.txt)
	if(EXISTS ${CMAKE_SOURCE_DIR}/${Y}/CMakeLists.txt)
		message(Found ${Y})
		add_subdirectory(${Y})
	endif()
endforeach()

