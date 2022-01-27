CC = cc
CFLAGS = -O2 -flto -pedantic -Wall -Wextra -Wpedantic $(shell pkg-config --cflags glib-2.0) -I./include
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)

$(YEAR)/$(DAY): $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY) ../data/$(YEAR)/$(DAY)/input.txt

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c lib/aoc_utils.o include/aoc_utils.h
	$(CC) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o -c $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c $(CFLAGS)

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY):	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o
	$(CC) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)  $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o $(LDFLAGS)
	@[ ! -e $@.exe ] || mv $@.exe $@

lib/aoc_utils.o:	lib/aoc_utils.c include/aoc_utils.h
	$(CC) -c -o lib/aoc_utils.o lib/aoc_utils.c $(CFLAGS)

../data/$(YEAR)/$(DAY)/test_input.txt:
	@echo "Need to generate a test_input.txt file for $(YEAR) day $(DAY)"

.PHONY:	templates run clean-all clean clean-executables


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



templates:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c
	 @../start_aoc.sh -l C -y $(YEAR) -d $(DAY) -t

../data/$(YEAR)/$(DAY)/input.txt $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c:	../start_aoc.sh
	../start_aoc.sh -f -l C -y $(YEAR) -d $(DAY)

clean-executables:
	find 2* -type f \( -name "*.stackdump" -o -name "*.exe" \) -delete
	find 2* -type f ! -name "*.?*" -delete

clean-objects:
	find . -type f -name "*.o" -delete

clean-all:	clean-executables clean-objects

clean:	clean-all


