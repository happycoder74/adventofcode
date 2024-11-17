cmake_minimum_required(VERSION 3.20)
project(advent-of-code LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AOC_YEARS
  2015 2016 2017 2018 2019 2020 2021 2022 2023
)

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


