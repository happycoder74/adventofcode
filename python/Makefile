SHELL=/bin/bash
PYTHONPATH=.
FILENAME=

$(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).py:
	../start_aoc.sh -y $(YEAR) -d $(DAY) -l python

.PHONY: run test clean

run: $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).py 
	@test -f ../data/$(YEAR)/$(DAY)/input.txt || ../start_aoc.sh -y $(YEAR) -d $(DAY) -o 
	@echo "Running AoC $(YEAR) - $(DAY)"
	@echo "============================"
	@PYTHONPATH=$(PYTHONPATH) python3 $(YEAR)/$(DAY)/aoc_$(YEAR)_$(DAY).py $(FILENAME)
	@echo "============================"

test:
	@echo "Running Test for AoC $(YEAR) - $(DAY)"
	@echo "============================"
	@PYTHONPATH=$(PYTHONPATH) pytest $(YEAR)/$(DAY)
	@echo "============================"

clean:
	find . \( -type f -name "*.pyc" -o -type d -name "__pycache__" \) -delete

