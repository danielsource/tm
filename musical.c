#include "raylib.h"

#define PROGRAM_TITLE "Musical"
#define PROGRAM_NAME "musical"
#define HUMAN_FINGERS 10
#define PIANO_KEYS 88

#pragma GCC diagnostic ignored "-Wunused-variable"

static void
draw(void) {
  BeginDrawing();
  ClearBackground(BLUE);
  EndDrawing();
}

int
main() {
  InitWindow(640, 480, PROGRAM_TITLE);
  int keyboard_pressed_once[HUMAN_FINGERS] = {0};
  int keyboard_pressed[HUMAN_FINGERS] = {0};
  while (!WindowShouldClose()) {
    draw();
  }
}

int key_to_note(int key) {
  switch (key) {             // 1 is A0,
  case KEY_Q:     return 28; // 28 is C3,
  case KEY_TWO:   return 29; // 29 is C#3,
  case KEY_W:     return 30; // 30 is D3, and so on.
  case KEY_THREE: return 31;
  case KEY_E:     return 32;
  case KEY_R:     return 33;
  case KEY_FIVE:  return 34;
  case KEY_T:     return 35;
  case KEY_SIX:   return 36;
  case KEY_Y:     return 37;
  case KEY_SEVEN: return 38;
  case KEY_U:     return 39;
  case KEY_I:                // 40 is middle C or C4.
  case KEY_Z:     return 40;
  case KEY_S:     return 41;
  case KEY_X:     return 42;
  case KEY_D:     return 43;
  case KEY_C:     return 44;
  case KEY_V:     return 45;
  case KEY_G:     return 46;
  case KEY_B:     return 47;
  case KEY_H:     return 48;
  case KEY_N:     return 49;
  case KEY_J:     return 50;
  case KEY_M:     return 51;
  case KEY_COMMA: return 52;
  default:        return 0;  // 0 means invalid note.
  }                          // 88 is C8.
}
