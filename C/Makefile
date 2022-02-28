CC = clang
DEBUG=-g
RELFLAGS= -O2 
GLIB_FLAGS != pkg-config --cflags glib-2.0
CFLAGS = -pedantic -Wall -Wextra -Wpedantic $(GLIB_FLAGS) -I./include
GLIB_LDFLAGS != pkg-config --libs glib-2.0
AOC_LIB = -laoc
LDFLAGS = -L./lib $(AOC_LIB) -lm $(GLIB_LDFLAGS) 
EXE = $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)
OBJS = $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o
SRCS = $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c lib/aoc_utils.c
INPUTFILE=input.txt
TESTINPUTFILE=test_input.txt

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c include/aoc_utils.h
	$(CC) $(RELFLAGS) $(CFLAGS) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o -c $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c 

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY):	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o $(AOC_LIB)
	$(CC) $(RELFLAGS) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)  $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o $(LDFLAGS)
	@[ ! -e $@.exe ] || mv $@.exe $@

$(AOC_LIB):	lib/libaoc.a

lib/libaoc.a: lib/*.c
	cd lib && $(MAKE)

../data/$(YEAR)/$(DAY)/test_input.txt:
	@echo "Need to generate a test_input.txt file for $(YEAR) day $(DAY)"

.PHONY:	templates run clean-all clean clean-all-executables clean-all-objects clean-objs


run:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY) 
	@test -f ../data/$(YEAR)/$(DAY)/input.txt || ../start_aoc.sh -y $(YEAR) -d $(DAY) -o 
	@test -f $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c || ../start_aoc.sh -y $(YEAR) -d $(DAY) -l C -t
	@echo "Running AoC $(YEAR) - $(DAY)"
	@echo "============================"
	@( cd $(YEAR)/$(DAY);  ./aoc_$(YEAR)_$(DAY) $(INPUTFILE); cd ../.. )
	@echo "============================"

test:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY) ../data/$(YEAR)/$(DAY)/$(TESTINPUTFILE)
	@echo "Running AoC $(YEAR) - $(DAY)"
	@echo "============================"
	@( cd $(YEAR)/$(DAY);  ./aoc_$(YEAR)_$(DAY) $(TESTINPUTFILE); cd ../.. )
	@echo "============================"

debug: clean-objs clean-exe
	$(CC) $(DEBUG) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

templates:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c
	 @../start_aoc.sh -l C -y $(YEAR) -d $(DAY) -t

clean-all-executables:
	find 2* -type f \( -name "*.stackdump" -o -name "*.exe" \) -delete
	find 2* -type f ! -name "*.?*" -delete

clean-all-objects:
	find . -type f -name "*.o" -delete

clean-all-libraries:
	find . -type f -name "*.a" -delete

clean-all:	clean-all-executables clean-all-objects clean-all-libraries

clean: clean-exe clean-objs

clean-exe:
	rm -f $(EXE) 

clean-objs:
	rm -f $(OBJS)

