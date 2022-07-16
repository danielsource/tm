#pragma once

#include "raylib.h"

#include "keyboard.h"

#define PROGRAM_NAME "tm"

struct palette {
  Color primarybg;
  Color secondarybg;
  Color tertiarybg;
  Color primaryfg;
  Color secondaryfg;
  Color tertiaryfg;
  Color light;
  Color dark;
};

#define PIANO_KEYS 88
struct piano {
  Sound sounds[PIANO_KEYS];
  int octaves;
};

struct guitar {
  int frets;
};

struct notation {
  int foo;
};

struct circle_of_fifths {
  int foo;
};

enum elementid {
  PIANO,
  GUITAR,
  NOTATION,
  CIRCLE_OF_FIFTHS,
  INPUTFIELD,
  ELEMENT_MAX
};

struct element {
  enum elementid id;
  union {
    struct piano piano;
    struct guitar guitar;
    struct notation notation;
    struct circle_of_fifths circle_of_fifths;
    struct inputfield inputfield;
  } u;
  char *name;
  int x, y, w, h;
};

enum mode { MARK, PLAY };

struct context {
  struct palette colors;
  struct element elements[ELEMENT_MAX];
  struct key2note_buffer pressed;
  struct key2note_buffer down;
  enum elementid focused;
  enum mode mode;
};

extern struct context Ctx;
