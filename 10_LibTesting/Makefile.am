# According to https://git.sr.ht/~frbrgeorge/namegen/tree/master/item/Makefile.am

.PHONY: clean

SUBDIRS = src tests

checklog:	check
	cat tests/*.log

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov

clean:
	git clean -df
