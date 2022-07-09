#pragma once

#include "layout.h"

struct lay_item;

struct piano {
  int octaves;
};

struct piano piano(int octaves);
void piano_draw(struct lay_item piano);
