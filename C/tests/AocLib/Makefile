TEST_SUITES=$(shell bash -c 'fd --max-depth 1 --type d --glob "a*"')

.PHONY:	all all-verbose

all:
	for suite in $(TEST_SUITES); do (cd $$suite; make test); done


all-verbose:
	for suite in $(TEST_SUITES); do (cd $$suite; make testverbose); done
