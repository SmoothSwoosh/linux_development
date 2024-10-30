.PHONY: clean
CC = cc
CFLAGS = -O0 -g
OUTPUT = output
EXPECTED_OUTPUT = expected_output
SCENARIOS = scenarios
TRASH = $(OUTPUT)
GENERATES = range

range: range.c

test: range
	@echo "Running scenarios..."

	@mkdir -p $(OUTPUT)
	@gdb ./range --batch --quiet -x $(SCENARIOS)/scenario1.gdb | grep "^@@@" > $(OUTPUT)/test1.out
	@gdb ./range --batch --quiet -x $(SCENARIOS)/scenario2.gdb | grep "^@@@" > $(OUTPUT)/test2.out

	@echo "Testing..."

	@diff $(OUTPUT)/test1.out $(EXPECTED_OUTPUT)/test1.out
	@diff $(OUTPUT)/test2.out $(EXPECTED_OUTPUT)/test2.out

	@echo "Tests passed"

clean:
	rm -rf $(TRASH) $(GENERATES)
