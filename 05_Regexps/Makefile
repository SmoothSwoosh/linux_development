.PHONY: run_binaries test clean
CC = cc
CFLAGS = -Wall
BINARIES = esub
OUTPUT = output
EXPECTED_OUTPUT = expected_output
TRASH = $(OUTPUT) $(EXPECTED_OUTPUT)
GENERATES = $(BINARIES)

esub: esub.c

run_binaries: $(BINARIES)
	@echo "Running binaries..."

	@mkdir $(OUTPUT)
	@mkdir $(EXPECTED_OUTPUT)
	@./esub "mba" "SHREK" "ambal" > $(OUTPUT)/output1.out
	@echo "ambal" | sed -E 's/mba/SHREK/' > $(EXPECTED_OUTPUT)/output1.out
	@./esub "shrek(T)shrek" "\0_\1" "ASdfasshrekTshrek" > $(OUTPUT)/output2.out
	@echo "ASdfasshrekTshrek" | sed -E 's/shrek(T)shrek/\0_\1/' > $(EXPECTED_OUTPUT)/output2.out

test: run_binaries
	@echo "Testing..."
	
	@cmp $(OUTPUT)/output1.out $(EXPECTED_OUTPUT)/output1.out
	@cmp $(OUTPUT)/output2.out $(EXPECTED_OUTPUT)/output2.out

	@echo "Tests passed"

clean:
	rm -rf $(TRASH) $(GENERATES)
