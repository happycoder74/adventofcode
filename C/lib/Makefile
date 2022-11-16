OUTPUTFILE=libaoc.a
GLIB_CFLAGS != pkg-config --cflags glib-2.0
LOCAL_CFLAGS = -I../include
CFLAGS = -g $(LOCAL_CFLAGS) $(GLIB_CFLAGS)
ARFLAGS = rcs

$(OUTPUTFILE):	aoc_utils.o aoc_grid.o aoc_sets.o aoc_timer.o ../include/*.h
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@


clean: 
	rm -f *.o
