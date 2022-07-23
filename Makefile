raylib_src   := third-party/raylib/src
libraylib    := $(raylib_src)/libraylib.a
cflags_debug := -ggdb -O0
cflags_warn  := -Wall -Wextra -Wpedantic
ldflags_old  := -lGL -lpthread -ldl -lrt -lX11

CC := gcc
LD := $(CC)
CFLAGS  := -I$(raylib_src) -std=c99 $(cflags_debug) $(cflags_warn)
LDFLAGS := -L$(raylib_src) -lraylib -lm $(ldflags_old)

all: musical

$(libraylib):
	$(MAKE) -C $(raylib_src) PLATFORM=PLATFORM_DESKTOP

musical: musical.c musical.h $(libraylib)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS)

run: all
	@./musical

clean:
	rm -f musical

.PHONY: all run clean
