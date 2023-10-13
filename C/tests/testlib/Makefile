CFLAGS = -g
all: 	libaoctest.a

libaoctest.a:	aoc_test.o
	$(AR) $(ARFLAGS) $@ $+

%.o:	%.c %.h

.PHONY: clean all

clean:
	@rm -rf *.o *.a

