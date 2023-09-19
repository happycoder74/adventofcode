set(AOC_DAY 03)
message(Currently in ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(aoc_${AOC_YEAR}_${AOC_DAY} 
    aoc_${AOC_YEAR}_${AOC_DAY}.cpp
    ${CMAKE_SOURCE_DIR}/lib/aoc_io.cpp
    )

target_include_directories(aoc_${AOC_YEAR}_${AOC_DAY} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(aoc_${AOC_YEAR}_${AOC_DAY} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

add_custom_target(run_${AOC_YEAR}_${AOC_DAY}
    COMMAND aoc_${AOC_YEAR}_${AOC_DAY}
    DEPENDS aoc_${AOC_YEAR}_${AOC_DAY}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)




