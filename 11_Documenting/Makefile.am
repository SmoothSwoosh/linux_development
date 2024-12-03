.PHONY: clean

LANG_FOLDER=ru/LC_MESSAGES
PROG=akinator

bin_PROGRAMS=$(PROG)

@DX_RULES@

doxygen-doc/man/man1/$(PROG).c.1:	doxygen-doc

man1_MANS=doxygen-doc/man/man1/$(PROG).c.1

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

all:	$(LANG_FOLDER)/$(PROG).mo doxygen-doc

ru.po:	$(PROG).c
	xgettext -k_ -c $(PROG).c -o $(PROG).pot
	msgmerge -U $@ $(PROG).pot

$(LANG_FOLDER)/$(PROG).mo:	ru.po
	mkdir -p $(LANG_FOLDER)
	msgfmt $< -o $@

http:	doxygen-doc
	python3 -m http.server --directory $</html 5000

clean:
	git clean -fd