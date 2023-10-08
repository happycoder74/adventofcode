CFLAGS = -g -I ../../testlib -I../../../include
LDLIBS = -laoc -laoctest
LDFLAGS = -L../../../debug/lib -L ../../testlib

TESTS = test_int32.o

test_aoc_array.exe:	test_aoc_array

test_aoc_array: test_aoc_array.o $(TESTS)

clean:
	@rm -rf .exe
	@rm -rf *.o

run: 	test_aoc_array.exe
	@./test_aoc_array.exe

