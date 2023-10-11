GLIB_CFLAGS=`pkg-config glib-2.0 --cflags`
GLIB_LDFLAGS=`pkg-config glib-2.0 --libs`
SYS_LIB_LOCATION=$(shell ([ -d /mingw64 ] && echo "mingw64") || echo "usr")
CRITERION_CFLAGS=-I/$(SYS_LIB_LOCATION)/local/include
CRITERION_LDLIBS=-L/$(SYS_LIB_LOCATION)/local/lib -lcriterion
AOC_CFLAGS=-I$(AOC_HOME)/include
AOC_LDFLAGS=-L$(AOC_HOME)/debug/lib -laoc
CFLAGS = -g $(AOC_CFLAGS) $(GLIB_CFLAGS) $(CRITERION_CFLAGS)
LDLIBS = $(GLIB_LDFLAGS) $(AOC_LDFLAGS) $(AOC_LIB) $(CRITERION_LDLIBS)
AOC_HOME=/home/$(USER)/projects/adventofcode/C

BIN=bin

AOC_LIBDIR=$(AOC_HOME)/debug/lib

SRC=$(AOC_HOME)/lib
SRCS=$(wildcard $(SRC)/*.c)

OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TESTS=$(wildcard test_aoc_*_array.c)

TESTBINS=$(patsubst %.c, $(BIN)/%.exe, $(TESTS))

## Build binary without running test
$(BIN)/%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

$(AOC_LIBDIR):	$(SRCS) $(AOC_HOME)/debug $(AOC_HOME)/include/*.h
	ninja -C $(AOC_HOME)/debug aoc

$(AOC_HOME)/debug:	$(AOC_HOME)/CMakeLists.txt
	cmake -B $(AOC_HOME)/debug -S $(AOC_HOME) -D CMAKE_BUILD_TYPE=Debug -G Ninja

test: $(AOC_LIBDIR)/libaoc.a $(BIN) $(TESTBINS) ## Run all tests
	@for test in $(TESTBINS); do echo "running $$test"; ./$$test; done

testverbose: $(AOC_LIBDIR)/libaoc.a $(BIN) $(TESTBINS) ## Run all tests in verbose mode
	@for test in $(TESTBINS); do echo "running $$test"; ./$$test --verbose; done

clean: ## Clean built files
	@rm -rf $(BIN)/*.exe
	@rm -rf $(OBJS)

run: 	test_aoc_array.exe
	@./test_aoc_array.exe

$(BIN):
	mkdir $@

MAKEFILE_LIST=Makefile

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
