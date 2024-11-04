.PHONY: clean

CC=cc
CFLAGS=-Wall
bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c
TESTS=sha1sum_test.sh md5sum_test.sh

test:
	@echo "Testing..."
	@echo -n 'Sha1 "SHREK' | ./rhasher | tail -n 1 > rhasher_output
	@echo -n "SHREK" | sha1sum | cut -f1 -d ' ' > sha1_output
	@diff rhasher_output sha1_output

	@echo -n 'Md5 "SHREK' | ./rhasher | tail -n 1 > rhasher_output
	@echo -n "SHREK" | md5sum | cut -f1 -d ' ' > md5_output
	@diff rhasher_output md5_output

	@echo "Tests passed"

clean:
	git clean -fd
