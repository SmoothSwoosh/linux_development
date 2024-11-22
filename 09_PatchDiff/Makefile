.PHONY: run clean
CC = cc
CFLAGS = -Wall
ORIGINAL = amazing0.c
GENERATES = amazing1.c amazing2.c amazing3.c amazing0 amazing1 amazing2 amazing3

sources: $(ORIGINAL)
	@patch -o amazing1.c < amazing1.patch
	@patch -o amazing2.c < amazing2.patch
	@patch -o amazing3.c < amazing3.patch

run: amazing0 amazing1 amazing2 amazing3
	@echo "Running...\n"

	./amazing0
	@echo

	./amazing1 8
	@echo

	./amazing2 '.#' 6
	@echo

	./amazing3 11 '.*' 7
	@echo

	@echo "Completed"

clean:
	rm -f $(GENERATES)
