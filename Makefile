all: musical

musical: musical.c
	chibicc -std=c99 -ggdb -O0 -o $@ $^ -lraylib -lm -Wall -Wextra -Wpedantic

run: all
	@./musical

clean:
	rm -f musical

.PHONY: all run clean
