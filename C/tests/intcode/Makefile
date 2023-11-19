# Compiler settings
CC=gcc
COMPILER_FLAGS=-g -ggdb -O0 -DNDEBUG -Wall -Wextra -pedantic -std=c99

#GLib specific variables
GLIB_CFLAGS=`pkg-config glib-2.0 --cflags`
GLIB_LDFLAGS=`pkg-config glib-2.0 --libs`

# Criterion specific variables
CRITERION_CFLAGS=-Ic:/Local/msys64/mingw64/local/include
CRITERION_LDLIBS=-Lc:/Local/msys64/mingw64/local/lib -lcriterion

AOC_HOME=c:/Local/msys64/home/yy11510/projects/adventofcode/C
AOC_BUILD=build
AOC_INCLUDES=-I$(AOC_HOME)/include
INTCODE_INCLUDES=-I$(AOC_HOME)/2019/intcode
GLIB_INCLUDES=`pkg-config --cflags glib-2.0`

AOC_LDLIBS=-L$(AOC_HOME)/$(AOC_BUILD)/lib -laoc
INTCODE_LDLIBS=$(AOC_HOME)/2019/intcode/intcode.c
GLIB_LDLIBS=`pkg-config --libs glib-2.0`

CFLAGS=$(COMPILER_FLAGS) $(AOC_INCLUDES) $(INTCODE_INCLUDES) $(GLIB_INCLUDES) $(CRITERION_CFLAGS)
LDLIBS=$(INTCODE_LDLIBS) $(AOC_LDLIBS) $(GLIB_LDLIBS) $(CRITERION_LDLIBS)

test_intcode.exe: test_intcode.c $(AOC_HOME)/$(AOC_BUILD)/lib/libaoc.a
	$(CC) -o test_intcode.exe $(CFLAGS) test_intcode.c $(LDLIBS)

run: test_intcode.exe
	./test_intcode.exe

verbose: test_intcode.exe
	./test_intcode.exe --verbose

.PHONY: clean

clean:
	-rm -f test_intcode.exe
