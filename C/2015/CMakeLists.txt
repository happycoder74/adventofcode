cmake_minimum_required(VERSION 3.12)
project (adventofcode C)
add_subdirectory(${PROJECT_SOURCE_DIR}/01)
add_subdirectory(${PROJECT_SOURCE_DIR}/02)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GLIB REQUIRED glib-2.0)


