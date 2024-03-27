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

find_package(PkgConfig REQUIRED)
pkg_search_module(PCRE2 REQUIRED libpcre2-posix)

find_package(PkgConfig REQUIRED)
pkg_search_module(CURL REQUIRED libcurl)

add_subdirectory(aoc_sets)
add_subdirectory(aoc_array)
add_subdirectory(aoc_hash)
add_subdirectory(aoc_grid)
add_subdirectory(aoc_string)
add_subdirectory(aoc_stack)
add_subdirectory(aoc_regex)

add_executable(aoc_lib_test
    ${CMAKE_SOURCE_DIR}/src/check_aoclib.c
    $<TARGET_OBJECTS:aoc_sets>
    $<TARGET_OBJECTS:aoc_array>
    $<TARGET_OBJECTS:aoc_hash>
    $<TARGET_OBJECTS:aoc_grid>
    $<TARGET_OBJECTS:aoc_string>
    $<TARGET_OBJECTS:aoc_stack>
    $<TARGET_OBJECTS:aoc_regex>
)

target_include_directories(
    aoc_lib_test
    PRIVATE ${CMAKE_SOURCE_DIR}/../../include
    PRIVATE ${CMAKE_SOURCE_DIR}
    PUBLIC ${CHECKLIB_INCLUDE_DIRS}
    PUBLIC ${PCRE2_INCLUDE_DIRS}
)


target_link_directories(
    aoc_lib_test
    PRIVATE ${CMAKE_SOURCE_DIR}/../../debug/lib
)

target_link_libraries(aoc_lib_test
    PRIVATE ${CMAKE_SOURCE_DIR}/../../debug/lib/libaoc.a
    ${GLIB_LINK_LIBRARIES}
    ${CURL_LINK_LIBRARIES}
    ${CHECKLIB_LINK_LIBRARIES}
    ${PCRE2_LINK_LIBRARIES}
    pthread
    m
)

add_custom_target(
    run_tests
    COMMAND aoc_lib_test
    DEPENDS aoc_lib_test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

message("GLIB_LINK_LIBRARIES = " ${GLIB_LINK_LIBRARIES})
message("CURL_LINK_LIBRARIES = " ${CURL_LINK_LIBRARIES})
message("CHECKLIB_LINK_LIBRARIES = " ${CHECKLIB_LINK_LIBRARIES})
message("PCRE2_LINK_LIBRARIES = " ${PCRE2_LINK_LIBRARIES})

message("GLIB_LIBRARIES = " ${GLIB_LIBRARIES})
message("CURL_LIBRARIES = " ${CURL_LIBRARIES})
message("CHECKLIB_LIBRARIES = " ${CHECKLIB_LIBRARIES})
message("PCRE2_LIBRARIES = " ${PCRE2_LIBRARIES})
