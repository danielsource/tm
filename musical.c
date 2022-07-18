// Main function on the end of this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#define PROGRAM_TITLE "Musical"
#define PROGRAM_NAME "musical"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

void
handle_keyboard(int pressed_once[], int pressed[], int len) {
  /* memset(pressed_once, 0, sizeof pressed_once[0] * len); */
  for (int i=0, key; i<len; i++) {
    key = GetKeyPressed();
    pressed_once[i] = key;
    if (!IsKeyDown(pressed[i]))
      pressed[i] = key;
  }
}

Sound *
getsound(const char *file_fmt, int idx) {
  enum { maxlen = 128 };
  Sound *sound = malloc(sizeof (Sound));
  char *file = malloc(maxlen * sizeof (char));
  snprintf(file, maxlen, file_fmt, idx);
  *sound = LoadSound(file);
  return sound;
}

void
play(int notes[], int len, Sound *sounds[], const char *file_fmt) {
  for (int i=0; i<len; i++) {
    if (!notes[i])
      return;
    Sound *sound = sounds[notes[i] - 1];
    if (!sound) {
      sound = getsound(file_fmt, notes[i]);
      sounds[notes[i] - 1] = sound;
    }
    PlaySoundMulti(*sound);
  }
}

void
draw(void) {
  BeginDrawing();
  ClearBackground(BLUE);
  EndDrawing();
}

int
key_to_note(int key) {
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

int
main() {
  enum item {
    PIANO,
    GUITAR,
    N_INSTRUMENTS,
    MUSICAL_NOTATION,
    CIRCLE_OF_FIFTHS,
    INPUT_OUTPUT_FIELD
  };
  enum {
    HUMAN_FINGERS = 10,
    PIANO_KEYS = 88
  };
  int pressed_once[HUMAN_FINGERS] = {0};
  int pressed[HUMAN_FINGERS] = {0};
  int notes[HUMAN_FINGERS] = {0};
  enum item focused = PIANO;
  Sound *sounds[N_INSTRUMENTS][PIANO_KEYS] = {0};
  const char *sound_file_fmts[N_INSTRUMENTS] = {
    "resources/sounds/piano-88-keys/%02d.mp3", NULL
  };
  InitAudioDevice();
  InitWindow(640, 480, PROGRAM_TITLE);
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    handle_keyboard(pressed_once, pressed, HUMAN_FINGERS);
    switch (focused) {
    case PIANO:
    case GUITAR:
      for (int i=0; i<HUMAN_FINGERS; i++) {
        notes[i] = key_to_note(pressed_once[i]);
        if (notes[i])
          printf("%d ", notes[i]); /* DEBUG */
      }
      if (notes[0]) {              /* DEBUG */
        putchar('\n');
        play(notes, HUMAN_FINGERS, sounds[focused], sound_file_fmts[focused]);
      }
    default:
      break;
    }
    draw();
  }
  StopSoundMulti();
  CloseAudioDevice();
  CloseWindow();
}
