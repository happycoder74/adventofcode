CC = cc
CFLAGS = -O2 -flto -pedantic -Wall $(shell pkg-config --cflags glib-2.0) -I./include
LDFLAGS = -lm $(shell pkg-config --libs glib-2.0)

$(YEAR)/$(DAY): $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c lib/aoc_utils.o include/aoc_utils.h
	$(CC) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o -c $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).c $(CFLAGS)

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY):	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o
	$(CC) -o $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)  $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).o lib/aoc_utils.o $(LDFLAGS)
	@[ ! -e $@.exe ] || mv $@.exe $@

lib/aoc_utils.o:	lib/aoc_utils.c include/aoc_utils.h
	$(CC) -c -o lib/aoc_utils.o lib/aoc_utils.c $(CFLAGS)

run:	$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY)
	( cd $(YEAR)/$(DAY);  ./aoc_$(YEAR)_$(DAY); cd ../.. )
