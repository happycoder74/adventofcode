# Compiler settings
CC=gcc
COMPILER_FLAGS=-g -Wall -Wextra -pedantic -std=c99

#GLib specific variables
GLIB_CFLAGS=`pkg-config glib-2.0 --cflags`
GLIB_LDFLAGS=`pkg-config glib-2.0 --libs`

SYS_LIB_LOCATION=$(shell ([ -d /mingw64 ] && echo "mingw64") || echo "usr")

# Criterion specific variables
CRITERION_CFLAGS=-I/$(SYS_LIB_LOCATION)/local/include
CRITERION_LDLIBS=-L/$(SYS_LIB_LOCATION)/local/lib -lcriterion

# AdventOfCode specific variables
AOC_HOME=/home/$(USER)/projects/adventofcode/C
AOC_CFLAGS=-I$(AOC_HOME)/include
AOC_LDFLAGS=-L$(AOC_HOME)/debug/lib -laoc
AOC_LIBDIR=$(AOC_HOME)/debug/lib

# Build the command line flags
CFLAGS = $(COMPILER_FLAGS) $(AOC_CFLAGS) $(GLIB_CFLAGS) $(CRITERION_CFLAGS)
LDLIBS = $(GLIB_LDFLAGS) $(AOC_LDFLAGS) $(AOC_LIB) $(CRITERION_LDLIBS)

# Build make variables used in targets
BIN=bin
MAKEFILE_LIST=Makefile

SRC=$(AOC_HOME)/lib
SRCS=$(wildcard $(SRC)/*.c)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TESTS=$(wildcard test_aoc_*_*.c)

TESTBINS=$(patsubst %.c, $(BIN)/%.exe, $(TESTS))

# Make targets
all: test ## Default target - equal to make test

test: $(TESTBINS) ## Run all tests
	@for test in $(TESTBINS); do printf "%s: " `basename $$test .exe`;./$$test; done

testverbose: $(AOC_LIBDIR) $(TESTBINS) ## Run all tests in verbose mode
	@for test in $(TESTBINS); do printf "running $$test: "; ./$$test --verbose; done

## Build binary without running test
$(BIN)/%.exe: %.c $(AOC_LIBDIR)/libaoc.a
	@if [ ! -d $(BIN) ]; then mkdir $(BIN); fi
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

$(AOC_LIBDIR)/libaoc.a:	$(SRCS) $(AOC_HOME)/include/*.h $(AOC_HOME)/CMakeLists.txt
	@ninja -C $(AOC_HOME)/debug aoc

.PHONY: clean bin help list


clean: ## Clean built files
	@rm -rf $(BIN)/*.exe
	@rm -rf $(OBJS)


$(BIN):
	@mkdir -p $@


list:
	@LC_ALL=C $(MAKE) -pRrq -f $(firstword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/(^|\n)# Files(\n|$$)/,/(^|\n)# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | grep -E -v -e '^[^[:alnum:]]' -e '^$@$$'

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'


build:	$(TESTBINS)	## Build tests, but dont run them.
