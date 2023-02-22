find_package(fmt REQUIRED)
add_executable(aoc_2017_01 aoc_2017_01.cpp)
target_include_directories(aoc_2017_01 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(aoc_2017_01 PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(aoc_2017_01 
	fmt
	aoc++)
add_custom_target(run_2017_01
    COMMAND aoc_2017_01.exe
    DEPENDS aoc_2017_01
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)


