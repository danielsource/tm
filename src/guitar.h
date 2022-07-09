#pragma once

#include "layout.h"

struct lay_item;

struct guitar {
  int frets;
};

struct guitar guitar(int octaves);
void guitar_draw(struct lay_item guitar);
