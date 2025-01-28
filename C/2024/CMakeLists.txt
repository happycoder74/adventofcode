aoc_generate_year_light(2024)

target_include_directories(aoc_2024_03 PRIVATE ${PCRE2POSIX_INCLUDE_DIRS})
target_link_libraries(aoc_2024_03 ${PCRE2POSIX_LDFLAGS})
