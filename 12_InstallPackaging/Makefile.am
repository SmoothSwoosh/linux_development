.PHONY: clean

if COND_GCOV
CFLAGS=-O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS=-O3 -g3
endif

LANG_FOLDER=ru/LC_MESSAGES

bin_PROGRAMS=main

main_SOURCES=akinator.c main.c
tests_SOURCES=tests.c akinator.c

@DX_RULES@

doxygen-doc/man/man1/akinator.c.1:	doxygen-doc

man1_MANS=doxygen-doc/man/man1/akinator.c.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

all:	$(LANG_FOLDER)/akinator.mo doxygen-doc

ru.po:	akinator.c
	xgettext -k_ -c akinator.c -o akinator.pot
	msgmerge -U $@ akinator.pot

$(LANG_FOLDER)/akinator.mo:	ru.po
	mkdir -p $(LANG_FOLDER)
	msgfmt $< -o $@

http:	doxygen-doc
	python3 -m http.server --directory $</html 5000

test: tests
	@./tests

install:
	@sudo mkdir -p /usr/local
	@sudo mkdir -p /usr/local/share/man/man1
	@sudo cp doxygen-doc/man/man1/akinator.c.1 /usr/local/share/man/man1/akinator.1
	@sudo cp main /usr/local/bin/akinator
	@sudo cp -r ru/LC_MESSAGES /usr/local/bin/LC_MESSAGES

uninstall:
	@sudo rm -rf /usr/local/bin/akinator
	@sudo rm -rf /usr/local/share/man/man1
	@sudo rm -rf /usr/local/bin/LC_MESSAGES

clean:
	git clean -df
