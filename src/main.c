#include <string.h>

#include "raylib.h" // The library that makes magic happen on the screen.

#include "main.h"
#include "keyboard.h"
#include "util.inc"

struct context Ctx; // Global struct that holds variables used in multiple functions.

static void init(void);
static void handle_input(void);
static void update(void);
static void draw(void);
static void play_audio(void);
static void quit(void);

int main(void) {
  init();
  while (!WindowShouldClose()) {
    handle_input();
    update();
    draw();
    play_audio();
  }
  quit();
  return 0;
}

void init(void) {
  Ctx.colors = (struct colors) {
    .primarybg   = GetColor(0x7CBFDAFF),
    .secondarybg = GetColor(0xDB7A7AFF),
    .tertiarybg  = GetColor(0xFFFFFFFF),
    .primaryfg   = GetColor(0x000000FF),
    .secondaryfg = GetColor(0xFFFFFFFF),
    .tertiaryfg  = GetColor(0x333333FF),
    .light       = GetColor(0xFFFFFFFF),
    .dark        = GetColor(0x000000FF),
  };
  Ctx.focused = PIANO;
  Ctx.mode = MARK|PLAY;
  Ctx.elements[PIANO]            = (struct element) { .name="piano", .id=PIANO, .x=0,.y=0,.w=300,.h=80 };
  Ctx.elements[GUITAR]           = (struct element) { .name="guitar", .id=GUITAR };
  Ctx.elements[NOTATION]         = (struct element) { .name="notation", .id=NOTATION };
  Ctx.elements[CIRCLE_OF_FIFTHS] = (struct element) { .name="circle of fifths", .id=CIRCLE_OF_FIFTHS };
  Ctx.elements[INPUTFIELD]       = (struct element) { .name="input field", .id=INPUTFIELD };
  memset(Ctx.down.keys, KEY_NULL, sizeof Ctx.down.keys);
  memset(Ctx.down.notes, NOTE_NULL, sizeof Ctx.down.notes);
  InitWindow(640, 480, PROGRAM_NAME);
  SetWindowPosition(20, 60);
  SetTargetFPS(60);
}

void handle_input(void) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
    Color auxbg = Ctx.colors.primarybg,
      auxfg = Ctx.colors.primaryfg;
    Ctx.colors.primarybg = Ctx.colors.secondarybg;
    Ctx.colors.primaryfg = Ctx.colors.secondaryfg;
    Ctx.colors.secondarybg = auxbg;
    Ctx.colors.secondaryfg = auxfg;
  }
  if (IsKeyPressed(KEY_TAB)) {
    if (IsKeyDown(KEY_LEFT_SHIFT)) {
      Ctx.focused = Ctx.focused ?
        (Ctx.focused - 1) % ELEMENT_MAX : ELEMENT_MAX - 1;
    } else {
      Ctx.focused = (Ctx.focused + 1) % ELEMENT_MAX;
    }
    LOGINFO("changed focus to %s (%d/%d)", Ctx.elements[Ctx.focused].name,
            Ctx.focused+1, ELEMENT_MAX);
  }
  switch (Ctx.focused) {
  case PIANO:
  case GUITAR:
  case NOTATION:
  case CIRCLE_OF_FIFTHS:
    key2note();
    return;
  case INPUTFIELD:
    key2inputfield();
    return;
  default:
    LOGINFO("invalid focused", 0);
    return;
  }
}

void update(void) {
}

void draw(void) {
  BeginDrawing();
  ClearBackground(Ctx.colors.primarybg);
  EndDrawing();
}

void play_audio(void) {

}

void quit(void) {
  CloseWindow();
}
