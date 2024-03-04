add_library(intcode
    intcode.c
	)
target_include_directories(intcode PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(intcode PRIVATE
    -Wall -Wextra -Wpedantic -Wno-error=unused -Wno-error=unused-parameter
	)


