#pragma once

#include "raylib.h"

#include "layout.h"

#define PROGRAM_NAME "tm"

struct colors {
  Color primarybg;
  Color secondarybg;
  Color tertiarybg;
  Color primaryfg;
  Color secondaryfg;
  Color tertiaryfg;
  Color light;
  Color dark;
};

extern struct context {
  struct colors colors;
  struct lay_context *layout;
} Ctx;
