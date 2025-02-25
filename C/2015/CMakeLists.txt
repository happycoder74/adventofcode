aoc_generate_year(2015)
target_link_libraries(aoc_2015_05 pcre2-posix)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

target_include_directories(aoc_2015_04 PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(aoc_2015_04 ${GLIB_LDFLAGS})
