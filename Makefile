CC := chibicc
LD := chibicc
CFLAGS := -DDEBUG -std=c99 -O0 -ggdb -Wall -Wextra
LDFLAGS := -lraylib -lm

objs_dir := build
program := tm
srcs := $(wildcard src/*.c)
heads := $(wildcard src/*.h)
objs := $(patsubst src/%.c,$(objs_dir)/%.o,$(srcs))

all: $(program)
$(program): $(objs)
	@echo LD $@
	@$(LD) -o $@ $^ $(LDFLAGS)

$(objs_dir)/%.o: src/%.c src/%.h src/util.h Makefile
	@echo CC $@
	@$(CC) -c $< $(CFLAGS) -o $@

$(objs): | $(objs_dir)
$(objs_dir):
	@mkdir $(objs_dir)

clean:
ifneq (,$(wildcard $(objs_dir)))
	@echo CLEAN
	@rm -f $(program)
	@rm -f $(objs_dir)/*
	@rmdir $(objs_dir)
endif

valgrind: $(program)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(objs_dir)/valgrind.log ./$(program)

run: $(program)
	@./$(program)

.PHONY: all clean valgrind run
