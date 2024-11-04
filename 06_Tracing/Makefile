.PHONY: test clean
CC = cc
CFLAGS = -Wall
BINARIES = move remove
TESTS = tests
PROTECT_LIB = protect_remove.so
TRASH = *.o *~ o.* *.out $(TESTS) PROTECT_input
GENERATES = $(BINARIES) $(PROTECT_LIB)

move: move.c

$(PROTECT_LIB): remove.c
	$(CC) -shared -o $@ $^

test: move $(PROTECT_LIB)
	@echo "Running tests..."

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@./move 2> /dev/null || test $$? = 1
	@test -f $(TESTS)/input
	@test ! -f $(TESTS)/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@strace -e read -P $(TESTS)/input -e fault=read ./move $(TESTS)/input $(TESTS)/output 2> /dev/null || test $$? = 2
	@test -f $(TESTS)/input
	@test ! -f $(TESTS)/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@strace -e write -e fault=write ./move $(TESTS)/input $(TESTS)/output 2> /dev/null || test $$? = 3
	@test -f $(TESTS)/input
	@test ! -f $(TESTS)/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@strace -e openat -P $(TESTS)/input -e fault=openat ./move $(TESTS)/input $(TESTS)/output 2> /dev/null || test $$? = 4
	@test -f $(TESTS)/input
	@test ! -f $(TESTS)/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@strace -e openat -P $(TESTS)/output -e fault=openat ./move $(TESTS)/input $(TESTS)/output 2> /dev/null || test $$? = 4
	@test -f $(TESTS)/input
	@test ! -f $(TESTS)/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@strace -e close -P $(TESTS)/input -e fault=close ./move $(TESTS)/input $(TESTS)/output 2> /dev/null || test $$? = 5
	@test ! -f $(TESTS)/input
	@test -f $(TESTS)/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > $(TESTS)/input
	@strace -e fault=write:error=EPERM:when=1 ./move $(TESTS)/input ${TESTS}/output 2> /dev/null || test $$? -eq 3
	@test -f $(TESTS)/input
	@test ! -f ${TESTS}/output
	@rm -rf $(TESTS)

	@mkdir $(TESTS)
	@echo "SHREK" > PROTECT_input
	@LD_PRELOAD=./$(PROTECT_LIB) ./move PROTECT_input $(TESTS)/output 2> /dev/null || test $$? = 0
	@test -f PROTECT_input
	@test -f $(TESTS)/output
	@rm -rf $(TESTS)

	@echo "Tests passed"

clean:
	rm -rf $(TRASH) $(GENERATES)
