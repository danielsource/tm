#include "raylib.h" // The library that makes magic happen on the screen.

#include "main.h"
#include "piano_draw.h"

struct context Ctx; // Global struct that holds variables used in multiple functions.

static void init(void);
static void input(void);
static void update(void);
static void draw(void);
static void quit(void);

int main(void) {
  init();
  while (!WindowShouldClose()) {
    input();
    update();
    draw();
  }
  quit();
  return 0;
}

void init(void) {
  int width = 640, height = 480, // 640x480 pixels window.
    target_fps = 60;
  Ctx.colors = (struct colors) {
    .primarybg   = GetColor(0x7CBFDAFF), // The hexadecimal color value #7cbfda.
    .secondarybg = GetColor(0xDB7A7AFF),
    .tertiarybg  = GetColor(0xFFFFFFFF),
    .primaryfg   = GetColor(0x000000FF),
    .secondaryfg = GetColor(0xFFFFFFFF),
    .tertiaryfg  = GetColor(0x333333FF),
    .light       = GetColor(0xFFFFFFFF),
    .dark        = GetColor(0x000000FF),
  };
  InitWindow(width, height, PROGRAM_NAME);
  SetTargetFPS(target_fps);
}

void input(void) {
  int note,
    key = GetKeyPressed();
  switch (key) {
  case KEY_NULL:             break;
  case KEY_Q:     note = 24; break; // 24 is C3,
  case KEY_TWO:   note = 25; break; // 25 is C#3,
  case KEY_W:     note = 26; break; // 26 is D3, and so on.
  case KEY_THREE: note = 27; break;
  case KEY_E:     note = 28; break;
  case KEY_R:     note = 29; break;
  case KEY_FIVE:  note = 30; break;
  case KEY_T:     note = 31; break;
  case KEY_SIX:   note = 32; break;
  case KEY_Y:     note = 33; break;
  case KEY_SEVEN: note = 34; break;
  case KEY_U:     note = 35; break;
  case KEY_Z:     note = 36; break;
  case KEY_S:     note = 37; break;
  case KEY_X:     note = 38; break;
  case KEY_D:     note = 39; break;
  case KEY_C:     note = 40; break;
  case KEY_V:     note = 41; break;
  case KEY_G:     note = 42; break;
  case KEY_B:     note = 43; break;
  case KEY_H:     note = 44; break;
  case KEY_N:     note = 45; break;
  case KEY_J:     note = 46; break;
  case KEY_M:     note = 47; break;
  case KEY_COMMA: note = 48; break;
  default:        note = -1;
  }
  if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
    Color auxbg = Ctx.colors.primarybg,
      auxfg = Ctx.colors.primaryfg;
    Ctx.colors.primarybg = Ctx.colors.secondarybg;
    Ctx.colors.primaryfg = Ctx.colors.secondaryfg;
    Ctx.colors.secondarybg = auxbg;
    Ctx.colors.secondaryfg = auxfg;
  }
}

void update(void) {
}

void draw(void) {
  BeginDrawing();
  ClearBackground(Ctx.colors.primarybg);
  piano_draw(0, 0, 300, 80);
  EndDrawing();
}

void quit(void) {
  CloseWindow();
}
