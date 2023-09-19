cmake_minimum_required(VERSION 3.15)
project(advent-of-code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AOC_YEARS
	2015 2016 2017 2018 2019 2020 2021 2022
	)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(AocGenerateDays)

set(CMAKE_BUILD_TYPE Release)

set(AOC_LIB_SOURCES
	${CMAKE_SOURCE_DIR}/lib/aoc_io.cpp
)

add_library(aoc++
	${AOC_LIB_SOURCES}
	)

target_include_directories(aoc++ PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(aoc++ PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wno-error=unused -Wno-error=unused-parameter
	)

foreach (Y ${AOC_YEARS})
	message(${CMAKE_SOURCE_DIR}/${Y}/CMakeLists.txt)
	if(EXISTS ${CMAKE_SOURCE_DIR}/${Y}/CMakeLists.txt)
		message(Found ${Y})
		add_subdirectory(${Y})
	endif()
endforeach()

