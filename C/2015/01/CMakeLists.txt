add_executable(aoc_2015_01 aoc_2015_01.c)

include_directories(
    ../../include
    ${GLIB_INCLUDE_DIRS}
    )

target_link_libraries(
    aoc_2015_01
    aoc
    ${GLIB_LIBRARIES}
    )
