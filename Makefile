CC ?= gcc
LD ?= $(CC)

raylib_src := ./third-party/raylib/src
libraylib  := $(raylib_src)/libraylib.a

CFLAGS_DEBUG := -ggdb -O0
CFLAGS_WARN  := -Wall -Wextra -Wpedantic
CFLAGS       := -I$(raylib_src) -std=c99 $(CFLAGS_DEBUG) $(CFLAGS_WARN)
LDFLAGS      := -L$(raylib_src) -lraylib -lm

all: musical

$(libraylib):
	$(MAKE) -C $(raylib_src) PLATFORM=PLATFORM_DESKTOP

musical: musical.c $(libraylib)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

run: all
	@./musical

clean:
	rm -f musical

.PHONY: all run clean
