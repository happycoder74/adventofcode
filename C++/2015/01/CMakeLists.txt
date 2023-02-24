find_package(fmt REQUIRED)
add_executable(aoc_2015_01 aoc_2015_01.cpp)
target_include_directories(aoc_2015_01 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(aoc_2015_01 PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(aoc_2015_01 fmt aoc++)
add_custom_target(run_2015_01
    COMMAND aoc_2015_01.exe
    DEPENDS aoc_2015_01
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
