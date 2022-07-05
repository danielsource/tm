#include <stdint.h>

#include <raylib.h>

struct screen {
  int width;
  int height;
};

static struct global_context {
  uint32_t flags;
  struct screen screen;
} Ctx;

#define PROGRAM_NAME "tm"

enum status {
  NOT_RUNNING = 0x00,
  RUNNING     = 0x01
};

static void init(void);
static void update(void);
static void draw(void);
static int quit(int);
