#pragma once

#include "raylib.h"

#define PROGRAM_NAME "tm"

extern struct context Ctx;

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

struct context {
  struct colors colors;
};
