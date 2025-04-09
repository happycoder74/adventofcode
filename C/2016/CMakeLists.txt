aoc_generate_year(2016)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
target_include_directories(aoc_2016_05 PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(aoc_2016_05 ${GLIB_LDFLAGS})

target_link_libraries(aoc_2016_07 pcre2-posix)
