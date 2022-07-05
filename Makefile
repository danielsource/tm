CC := gcc
LD := gcc
CFLAGS := -std=c99 -pedantic -Wall -Wextra
LDFLAGS := -lraylib -lm

objs_dir := build
program := $(objs_dir)/tm
srcs := $(wildcard src/*.c)
heads := $(wildcard src/*.h)
objs := $(patsubst src/%.c,$(objs_dir)/%.o,$(srcs))

all: $(program)
$(program): $(objs)
	$(LD) -o $@ $^ $(LDFLAGS)

$(objs_dir)/%.o: src/%.c src/%.h src/main.h
	$(CC) -c $< $(CFLAGS) -o $@

$(objs_dir)/main.o: src/main.c $(heads)
	$(CC) -c $< $(CFLAGS) -o $@

$(objs): | $(objs_dir)
$(objs_dir):
	mkdir $(objs_dir)

clean:
ifneq (,$(wildcard $(objs_dir)))
	rm -f $(objs_dir)/*
	rmdir $(objs_dir)
endif

run: $(program)
	@./$(program)

.PHONY: all clean run
