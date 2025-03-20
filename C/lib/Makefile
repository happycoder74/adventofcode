OUTPUTFILE=libaoc.a
LOCAL_CFLAGS = -I../include
CFLAGS = -O2 $(LOCAL_CFLAGS)
ARFLAGS = rcs

OBJS := $(patsubst %.c,%.o,$(wildcard *.c))

$(OUTPUTFILE): $(OBJS)
	$(AR) $(ARFLAGS) $@ $?
	ranlib $@

clean:
	rm -f *.o libaoc.a *.dll
