.PHONY: clean
CC = cc
CFLAGS = -Wall -fPIC
STATIC_LIB = liboutput_static.a
SHARED_LIB = liboutput.so
BINARIES = prog prog-a prog-so
TESTS = ut
TRASH = *.o *~ o.* *.out $(TESTS)
GENERATES = $(BINARIES) $(STATIC_LIB) $(SHARED_LIB)

all: $(BINARIES)

$(STATIC_LIB): fun.o const.o
	ar -rcs $@ $^

$(SHARED_LIB): fun.o const.o
	$(CC) -shared -o $@ $^

prog: prog.o fun.o const.o

prog-a: prog.o $(STATIC_LIB)
	$(CC) $< -L. -loutput_static -o $@

prog-so: prog.o $(SHARED_LIB)
	$(CC) $< -L. -loutput -o $@

prog.o: prog.c outlib.h

fun.o: fun.c outlib.h

const.o: const.c

run_binaries: $(BINARIES)
	@echo "Running binaries..."

	@mkdir -p $(TESTS)
	@./prog > $(TESTS)/prog1.out 2>&1
	@./prog-a > $(TESTS)/prog-a1.out 2>&1
	@LD_LIBRARY_PATH=$(PWD) ./prog-so > $(TESTS)/prog-so1.out 2>&1

	@./prog param1 > $(TESTS)/prog2.out 2>&1
	@./prog-a param1 > $(TESTS)/prog-a2.out 2>&1
	@LD_LIBRARY_PATH=$(PWD) ./prog-so > $(TESTS)/prog-so2.out param1 2>&1

	@./prog param1 param2 param3 > $(TESTS)/prog3.out 2>&1
	@./prog-a param1 param2 param3 > $(TESTS)/prog-a3.out 2>&1
	@LD_LIBRARY_PATH=$(PWD) ./prog-so param1 param2 param3 > $(TESTS)/prog-so3.out 2>&1

test: run_binaries
	@echo "Running tests..."

	@cmp $(TESTS)/prog1.out $(TESTS)/prog-a1.out && cmp $(TESTS)/prog1.out $(TESTS)/prog-so1.out
	@cmp $(TESTS)/prog2.out $(TESTS)/prog-a2.out && cmp $(TESTS)/prog2.out $(TESTS)/prog-so2.out
	@cmp $(TESTS)/prog3.out $(TESTS)/prog-a3.out && cmp $(TESTS)/prog3.out $(TESTS)/prog-so3.out

	@echo "Tests passed"

clean:
	rm -rf $(TRASH) $(GENERATES)
