all: musical

musical: musical.c
	gcc -o $@ $^ -std=c99 -ggdb -O0 -lraylib -lm -Wall -Wextra -Wpedantic

run: all
	@./musical

clean:
	rm -f musical

.PHONY: all run clean
