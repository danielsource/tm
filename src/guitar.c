#include "raylib.h"

#include "layout.h"
#include "main.h"
#include "guitar.h"

struct guitar
guitar(int frets) {
  return (struct guitar) { .frets = frets };
}

void
guitar_draw(struct lay_item guitar) {
  DrawRectangleRec(guitar.rect, Ctx.colors.secondarybg);
}
