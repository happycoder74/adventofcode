function (AOC_GENERATE YEAR DAY)
    add_executable(aoc_${YEAR}_${DAY}
        ${DAY}/aoc_${YEAR}_${DAY}.c)
    target_include_directories(aoc_${YEAR}_${DAY} PRIVATE ${GLIB_INCLUDE_DIRS})
    target_include_directories(aoc_${YEAR}_${DAY} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(aoc_${YEAR}_${DAY} ${GLIB_LDFLAGS})
    target_link_libraries(aoc_${YEAR}_${DAY}
        aoc
        glib-2.0
        m
        )
    target_compile_options(
        aoc_${YEAR}_${DAY}
        PUBLIC
        -Wall -Wextra -pedantic -Wno-error=unused -Wno-error=unused-parameter -Wno-error=unused-variable
        )
    add_custom_target(run_${YEAR}_${DAY}
        COMMAND aoc_${YEAR}_${DAY}
        DEPENDS aoc_${YEAR}_${DAY}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    add_custom_target(test_${YEAR}_${DAY}
        COMMAND aoc_${YEAR}_${DAY} --test
        DEPENDS aoc_${YEAR}_${DAY}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
endfunction()

function(AOC_GENERATE_YEAR AOC_YEAR)
    set(DAY_DIRECTORIES
        01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
        )
    set(custom_target_args)
    foreach (DIR ${DAY_DIRECTORIES})
        if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})
            AOC_GENERATE(${AOC_YEAR} ${DIR})
            list(APPEND custom_target_args COMMAND ${AOC_YEAR}/aoc_${AOC_YEAR}_${DIR})
            list(APPEND custom_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
        else()
            message("Skipping ${DIR}")
        endif()
    endforeach()

    add_custom_target(
        run_${AOC_YEAR}
        ${custom_target_args}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
endfunction()

