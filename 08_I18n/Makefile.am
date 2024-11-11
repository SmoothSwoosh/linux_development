.PHONY: clean

bin_PROGRAMS=akinator

LANG_FOLDER=ru/LC_MESSAGES
PROG=akinator

all: $(LANG_FOLDER)/$(PROG).mo

ru.po: $(PROG).c
	xgettext -k_ -c $(PROG).c -o $(PROG).pot
	msgmerge -U $@ $(PROG).pot

$(LANG_FOLDER)/$(PROG).mo: ru.po
	mkdir -p $(LANG_FOLDER)
	msgfmt $< -o $@

clean:
	git clean -fd
