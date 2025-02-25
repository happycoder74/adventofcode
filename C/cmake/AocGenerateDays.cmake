function(aoc_generate YEAR DAY)
  add_executable(aoc_${YEAR}_${DAY} aoc_${YEAR}_${DAY}.c)
  target_include_directories(aoc_${YEAR}_${DAY}
                             PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(aoc_${YEAR}_${DAY} aoc m)
  if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "OpenBSD")
    target_link_libraries(aoc_${YEAR}_${DAY} $<$<CONFIG:MEMDEBUG>:dl>
                          $<$<CONFIG:DEBUGVERBOSE>:dl>)
  endif()
  add_custom_target(
    run_${YEAR}_${DAY}
    COMMAND aoc_${YEAR}_${DAY}
    DEPENDS aoc_${YEAR}_${DAY}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  add_custom_target(
    test_${YEAR}_${DAY}
    COMMAND aoc_${YEAR}_${DAY} --test
    DEPENDS aoc_${YEAR}_${DAY}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

function(aoc_generate_light YEAR DAY)
  add_executable(aoc_${YEAR}_${DAY} aoc_${YEAR}_${DAY}.c)
  target_include_directories(aoc_${YEAR}_${DAY}
                             PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(aoc_${YEAR}_${DAY} aoclight m)
  if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "OpenBSD")
    target_link_libraries(aoc_${YEAR}_${DAY} $<$<CONFIG:MEMDEBUG>:dl>
                          $<$<CONFIG:DEBUGVERBOSE>:dl>)
  endif()
  add_custom_target(
    run_${YEAR}_${DAY}
    COMMAND aoc_${YEAR}_${DAY}
    DEPENDS aoc_${YEAR}_${DAY}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  add_custom_target(
    test_${YEAR}_${DAY}
    COMMAND aoc_${YEAR}_${DAY} --test
    DEPENDS aoc_${YEAR}_${DAY}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

function(aoc_generate_year AOC_YEAR)
  set(DAY_DIRECTORIES
      01
      02
      03
      04
      05
      06
      07
      08
      09
      10
      11
      12
      13
      14
      15
      16
      17
      18
      19
      20
      21
      22
      23
      24
      25)
  set(custom_target_args)
  set(custom_test_target_args)
  set(custom_build_target_args)
  foreach(DIR ${DAY_DIRECTORIES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/aoc_${AOC_YEAR}_${DIR}.c)
      aoc_generate(${AOC_YEAR} ${DIR})
      list(APPEND custom_target_args COMMAND ${AOC_YEAR}/aoc_${AOC_YEAR}_${DIR})
      list(APPEND custom_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
      list(APPEND custom_test_target_args COMMAND
           ${AOC_YEAR}/aoc_${AOC_YEAR}_${DIR} --test)
      list(APPEND custom_test_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
      list(APPEND custom_build_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
    else()
      message("Skipping ${DIR}")
    endif()
  endforeach()

  add_custom_target(aoc_${AOC_YEAR} ${custom_build_target_args})

  add_custom_target(
    run_${AOC_YEAR}
    ${custom_target_args}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  add_custom_target(
    test_${AOC_YEAR}
    ${custom_target_args}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

function(aoc_generate_year_light AOC_YEAR)
  set(DAY_DIRECTORIES
      01
      02
      03
      04
      05
      06
      07
      08
      09
      10
      11
      12
      13
      14
      15
      16
      17
      18
      19
      20
      21
      22
      23
      24
      25)
  set(custom_target_args)
  set(custom_test_target_args)
  set(custom_build_target_args)
  foreach(DIR ${DAY_DIRECTORIES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/aoc_${AOC_YEAR}_${DIR}.c)
      aoc_generate_light(${AOC_YEAR} ${DIR})
      list(APPEND custom_target_args COMMAND ${AOC_YEAR}/aoc_${AOC_YEAR}_${DIR})
      list(APPEND custom_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
      list(APPEND custom_test_target_args COMMAND
           ${AOC_YEAR}/aoc_${AOC_YEAR}_${DIR} --test)
      list(APPEND custom_test_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
      list(APPEND custom_build_target_args DEPENDS aoc_${AOC_YEAR}_${DIR})
    else()
      message("Skipping ${DIR}")
    endif()
  endforeach()

  add_custom_target(aoc_${AOC_YEAR} ${custom_build_target_args})

  add_custom_target(
    run_${AOC_YEAR}
    ${custom_target_args}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  add_custom_target(
    test_${AOC_YEAR}
    ${custom_test_target_args}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()
