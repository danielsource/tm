#include "raylib.h" // The library that makes magic happen on the screen.

#include "main.h"
#include "keyboard.h"
#include "util.h"

struct context Ctx; // Global struct that holds variables used in multiple functions.

static void init(void);
static void handle_input(void);
static void update(void);
static void draw(void);
static void play(int len, int notes[len]);
static void quit(void);

int
main(void) {
  init();
  while (!WindowShouldClose()) {
    handle_input();
    update();
    draw();
    play(LENGTH(Ctx.pressed.notes), Ctx.pressed.notes);
  }
  quit();
  return 0;
}

void
init(void) {
  Ctx.colors = (struct palette) {
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
  Ctx.elements[PIANO] = (struct element) {
    .name="piano", .id=PIANO, .x=0,.y=0,.w=300,.h=80 };
  Ctx.elements[GUITAR] = (struct element) {
    .name="guitar", .id=GUITAR };
  Ctx.elements[NOTATION] = (struct element) {
    .name="notation", .id=NOTATION };
  Ctx.elements[CIRCLE_OF_FIFTHS] = (struct element) {
    .name="circle of fifths", .id=CIRCLE_OF_FIFTHS };
  Ctx.elements[INPUTFIELD] = (struct element) {
    .name="input field", .id=INPUTFIELD };
  InitAudioDevice();
  struct piano *piano = &Ctx.elements[PIANO].u.piano;
  enum { fn = 32, flag = 2 };
  const char fmt[fn + flag] = "res/sounds/piano-88-keys/%02d.mp3";
  char filename[fn];
  for (int i=0; i<PIANO_KEYS; i++) {
    snprintf(filename, fn, fmt, i);
    piano->sounds[i] = LoadSound(filename);
  }
  InitWindow(640, 480, PROGRAM_NAME);
  SetWindowPosition(20, 60);
  SetTargetFPS(60);
}

void
handle_input(void) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
    Color auxbg = Ctx.colors.primarybg,
      auxfg = Ctx.colors.primaryfg;
    Ctx.colors.primarybg = Ctx.colors.secondarybg;
    Ctx.colors.primaryfg = Ctx.colors.secondaryfg;
    Ctx.colors.secondarybg = auxbg;
    Ctx.colors.secondaryfg = auxfg;
  }
  if (IsKeyPressed(KEY_TAB)) {
    if (IsKeyDown(KEY_LEFT_SHIFT))
      Ctx.focused = (Ctx.focused) ?
        (Ctx.focused - 1) % ELEMENT_MAX : ELEMENT_MAX - 1;
    else
      Ctx.focused = (Ctx.focused + 1) % ELEMENT_MAX;
    LOGINFO("changed focus to %s (%d/%d)",
            Ctx.elements[Ctx.focused].name,
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

void
update(void) {
}

void
draw(void) {
  BeginDrawing();
  ClearBackground(Ctx.colors.primarybg);
  EndDrawing();
}

void
play(int len, int notes[len]) {
  Sound *sounds;
  int c4_transposing;
  switch (Ctx.focused) {
  case PIANO:
    sounds = Ctx.elements[PIANO].u.piano.sounds;
    c4_transposing = 3;
    break;
  default:
    return;
  }
  for (int i=0; i<len; i++) {
    if (notes[i] == NOTE_NULL)
      break;
    PlaySoundMulti(sounds[notes[i] + c4_transposing]);
    LOGINFO("playing %d", notes[i]);
  }
}

void
quit(void) {
  StopSoundMulti();
  for (int i=0; i<PIANO_KEYS; i++)
    UnloadSound(Ctx.elements[PIANO].u.piano.sounds[i]);
  CloseAudioDevice();
  CloseWindow();
}
