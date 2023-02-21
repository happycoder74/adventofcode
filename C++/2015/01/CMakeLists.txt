find_package(fmt REQUIRED)
add_executable(aoc_2015_01 aoc_2015_01.cpp)
target_link_libraries(aoc_2015_01 fmt)
add_custom_target(run
    COMMAND aoc_2015_01.exe
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
