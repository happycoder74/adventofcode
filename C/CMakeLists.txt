cmake_minimum_required(VERSION 3.12)
project (adventofcode C)
add_subdirectory(${PROJECT_SOURCE_DIR}/2015)
add_subdirectory(${PROJECT_SOURCE_DIR}/2016)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
link_directories(${GLIB_LIBRARY_DIRS})

