CC = cc
CFLAGS = -Wall
bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c
TESTS = sha1_test.sh md5_test.sh
GENERATES = test-driver *.m4 *.cache compile *.in configure depcomp install-sh missing build *~

sha1_test.sh:
	@echo 'echo "SHREK" > sha1_input' >> $@
	@echo 'echo -n "> " > sha1_output' >> $@
	@echo 'sha1sum sha1_input | cut -d " " -f 1 >> sha1_output' >> $@
	@echo 'echo -n "Sha1 sha1_input" | ./rhasher | head -n 1 > rhasher_sha1.out' >> $@
	@echo 'cmp sha1_output rhasher_sha1.out' >> $@
	@chmod +x $@

md5_test.sh:
	@echo 'echo "SHREK" > md5_input' >> $@
	@echo 'echo -n "> " > md5_output' >> $@
	@echo 'md5sum md5_input | cut -d " " -f 1 >> md5_output' >> $@
	@echo 'echo -n "Md5 md5_input" | ./rhasher | head -n 1 > rhasher_md5.out' >> $@
	@echo 'cmp md5_output rhasher_md5.out' >> $@
	@chmod +x $@

clean:
	rm -rf $(GENERATES)
