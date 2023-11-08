TEST_SUITES=$(shell find . -maxdepth 1 -type d -name "a*")

.PHONY:	all all-verbose

all:
	for suite in $(TEST_SUITES); do (cd $$suite; make test); done


all-verbose:
	for suite in $(TEST_SUITES); do (cd $$suite; make testverbose); done
