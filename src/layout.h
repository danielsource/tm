#pragma once

#include <stdlib.h>

#include "raylib.h"

#include "guitar.h"
#include "piano.h"
#include "util.h"

enum lay_type { lay_piano, lay_guitar, lay_generic };

struct guitar;
struct piano;
union lay_u {
  struct guitar guitar;
  struct piano piano;
};

struct lay_item {
  enum lay_type type;
  Rectangle rect;
  void (*draw)(struct lay_item *self);
  union lay_u this;
};

struct lay_context {
  struct lay_item *items;
  Rectangle root;
  int count;
  int capacity;
};

struct lay_context *lay_context(Rectangle root, int count);
void lay_additem(struct lay_context *ctx, enum lay_type type, Rectangle rect, union lay_u this);
void lay_makelist(struct lay_context *ctx, int gap);
void lay_draw(struct lay_context *ctx);
void lay_destroy(struct lay_context *ctx);
