OUTPUTFILE=libaoc.a
GLIB_CFLAGS != pkg-config --cflags glib-2.0
LOCAL_CFLAGS = -I../include
CFLAGS = $(LOCAL_CFLAGS) $(GLIB_CFLAGS)
ARFLAGS = rcs

$(OUTPUTFILE):	aoc_utils.o aoc_grid.o aoc_sets.o ../include/*.h
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@
