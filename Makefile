include os.mk

CFLAGS := $(CCFLAGS) -I/usr/include/SDL2 -D_REENTRANT -Wall -Wextra -ansi -pedantic -O0 -ggdb
LDFLAGS := -Wl,-Bstatic -pthread -lSDL2 -Wl,-Bdynamic -lm

objs := $(subst src/,$(build_dir)/,$(patsubst %.c,%.o,$(wildcard src/*.c)))
program := $(build_dir)/bin/tm

.PHONY: all
all: $(program)

.PHONY: clean
clean:
	rm -fr $(build_dir)

.PHONY: run
run: all
	$(program)

.PHONY: run-st
run-st: all
	st -g 50x10+1300+700 -e $(program)

$(program): $(objs) | $(build_dir)/bin
	$(CC) $^ -o $@ $(LDFLAGS)

$(build_dir)/%.o: src/%.c $(wildcard src/*.h)
	$(CC) $(CFLAGS) -c $< -o $@

$(objs): | $(build_dir)

$(build_dir): | build
	mkdir $(build_dir)

$(build_dir)/bin:
	mkdir $(build_dir)/bin

build:
	mkdir build
