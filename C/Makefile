CC = cc
DEBUG=-g
RELFLAGS= -O2 -flto
CFLAGS = -pedantic -Wall -Wextra -Wpedantic $(shell pkg-config --cflags glib-2.0) -I./include
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)
EXE = $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)
OBJS = $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o
SRCS = $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c lib/aoc_utils.c

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c include/aoc_utils.h
	$(CC) $(RELFLAGS) $(CFLAGS) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o -c $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c 

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY):	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o
	$(CC) $(RELFLAGS) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)  $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o $(LDFLAGS)
	@[ ! -e $@.exe ] || mv $@.exe $@

lib/aoc_utils.o:	lib/aoc_utils.c include/aoc_utils.h
	$(CC) $(RELFLAGS) $(CFLAGS) -c -o lib/aoc_utils.o lib/aoc_utils.c 

../data/$(YEAR)/$(DAY)/test_input.txt:
	@echo "Need to generate a test_input.txt file for $(YEAR) day $(DAY)"

.PHONY:	templates run clean-all clean clean-all-executables clean-all-objects clean-objs


run:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY) ../data/$(YEAR)/$(DAY)/input.txt
	@echo "Running AoC $(YEAR) - $(DAY)"
	@echo "============================"
	@( cd $(YEAR)/$(DAY);  ./aoc_$(YEAR)_$(DAY); cd ../.. )
	@echo "============================"

test:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY) ../data/$(YEAR)/$(DAY)/test_input.txt
	@echo "Running AoC $(YEAR) - $(DAY)"
	@echo "============================"
	@( cd $(YEAR)/$(DAY);  ./aoc_$(YEAR)_$(DAY) test_input.txt; cd ../.. )
	@echo "============================"

debug: clean-objs clean-exe
	$(CC) $(DEBUG) $(CFLAGS) -o $(EXE) $(SRCS) $(LDFLAGS)

templates:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c
	 @../start_aoc.sh -l C -y $(YEAR) -d $(DAY) -t

../data/$(YEAR)/$(DAY)/input.txt $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c:	../start_aoc.sh
	../start_aoc.sh -f -l C -y $(YEAR) -d $(DAY)

clean-all-executables:
	find 2* -type f \( -name "*.stackdump" -o -name "*.exe" \) -delete
	find 2* -type f ! -name "*.?*" -delete

clean-all-objects:
	find . -type f -name "*.o" -delete

clean-all:	clean-all-executables clean-all-objects

clean: clean-exe clean-objs

clean-exe:
	rm -f $(EXE) 

clean-objs:
	rm -f $(OBJS)


