cmake_minimum_required(VERSION 3.10.1)
project(advent-of-code)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_subdirectory(2015/01)
add_subdirectory(2017/01)
add_subdirectory(lib)


