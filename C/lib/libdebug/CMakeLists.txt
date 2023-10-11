add_library(aocmemdbg STATIC
    aoc_mem.c
	)
target_include_directories(aocmemdbg PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(aocmemdbg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(aocmemdbg PRIVATE ${GLIB_INCLUDE_DIRS})
target_compile_options(aocmemdbg PRIVATE
    -Wall -Wextra -Wpedantic -Werror -Wno-error=unused -Wno-error=unused-parameter
	)


