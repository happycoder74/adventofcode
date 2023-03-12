set(AOC_YEAR 2021)
set(DAY_DIRECTORIES
	01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
	)	

foreach (DIR ${DAY_DIRECTORIES})
	if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})
		AOC_GENERATE(${AOC_YEAR} ${DIR})
	else()
		message("Skipping ${DIR}")
	endif()
endforeach()

target_link_libraries(aoc_2021_03 m)
target_link_libraries(aoc_2021_08 m)

