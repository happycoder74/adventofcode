OUTPUTFILE=libaoc.a
GLIB_CFLAGS != pkg-config --cflags glib-2.0
LOCAL_CFLAGS = -I../include
CFLAGS = -O2 $(LOCAL_CFLAGS) $(GLIB_CFLAGS)
ARFLAGS = rcs

OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

$(OUTPUTFILE): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?
	ranlib $@

clean: 
	rm -f *.o libaoc.a *.dll
