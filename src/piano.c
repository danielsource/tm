#include "raylib.h"

#include "layout.h"
#include "main.h"
#include "piano.h"

struct piano
piano(int octaves) {
  return (struct piano) { .octaves = octaves };
}

void
piano_draw(struct lay_item *self) {
  struct lay_item *item = self;
  DrawRectangleRec(item->rect, Ctx.colors.secondarybg);
}
