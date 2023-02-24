find_package(fmt REQUIRED)
add_executable(aoc_2021_01 aoc_2021_01.cpp)
target_include_directories(aoc_2021_01 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(aoc_2021_01 PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(aoc_2021_01 
	fmt
	aoc++)
add_custom_target(run_2021_01
    COMMAND aoc_2021_01.exe
    DEPENDS aoc_2021_01
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)



