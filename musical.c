#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#define PROGRAM_TITLE "Musical"
#define PROGRAM_NAME  "musical"

enum item {
  PIANO,
  GUITAR,
  N_INSTRUMENTS,
  MUSICAL_NOTATION,
  CIRCLE_OF_FIFTHS,
  INPUT_OUTPUT_FIELD,
  N_ITEMS
};

enum scalar {
  WINDOW_WIDTH  = 640,
  WINDOW_HEIGHT = 480,
  WINDOW_POS_X  = 20,
  WINDOW_POS_Y  = 60,
  HUMAN_FINGERS = 10,
  PIANO_KEYS    = 88,
  NOTE_NAME_MAXLEN = 6 // Including null char.
};

enum language {
  ENGLISH,
  PORTUGUESE,
  N_LANGUAGES
};

enum octave {
  C,     // Dó,
  CS,    // Dó sustenido,
  D,     // Ré,
  DS,    // Ré sustenido,
  E,     // Mi,
  F,     // Fá,
  FS,    // Fá sustenido,
  G,     // Sol,
  GS,    // Sol sustenido,
  A,     // Lá,
  AS,    // Lá sustenido,
  B,     // Si.
  OCTAVE // Chromatic scale length (12).
};

const char *note_names[N_LANGUAGES][OCTAVE] = {
  { "C",   "C#",  "D",    "D#",  "E",   "F",
    "F#",  "G",   "G#",   "A",   "A#",  "B" },
  { "Dó",  "Dó#", "Ré",   "Ré#", "Mi",  "Fá",
    "Fá#", "Sol", "Sol#", "Lá",  "Lá#", "Si" }
};

void
init(void) {
  SetTraceLogLevel(LOG_WARNING);
  InitAudioDevice();
  InitWindow(WINDOW_WIDTH,
             WINDOW_HEIGHT,
             PROGRAM_TITLE);
  SetWindowPosition(WINDOW_POS_X,
                    WINDOW_POS_Y);
  SetTargetFPS(60);
}

void
handle_keyboard(int pressed_once[HUMAN_FINGERS],
                int pressed[HUMAN_FINGERS]) {
  for (int i = 0, key; i < HUMAN_FINGERS; i++) {
    key = GetKeyPressed();
    pressed_once[i] = key;
    if (!IsKeyDown(pressed[i]))
      pressed[i] = key;
  }
}

void
handle_input(int pressed_once[HUMAN_FINGERS],
             int pressed[HUMAN_FINGERS]) {
  handle_keyboard(pressed_once, pressed);
}

void
die(const char *msg) {
  fprintf(stderr, PROGRAM_NAME " crashed: %s\n", msg);
  exit(1);
}

Sound *
get_sound(const char *file_fmt, int idx) {
  enum { maxlen = 128 };
  Sound *sound = malloc(sizeof (Sound));
  char file[maxlen];
  snprintf(file, maxlen, file_fmt, idx);
  *sound = LoadSound(file);
  if (!sound->frameCount) // NOTE: I don't know if this
                          // is a safe way to check
                          // if sound is ok.
    die("Sound file not found.");
  return sound;
}

void
play(int notes[], int len, Sound *sounds[], const char *file_fmt) {
  for (int i = 0; notes[i] && i < len; i++) {
    Sound *sound = sounds[notes[i] - 1];
    if (!sound) {
      sound = get_sound(file_fmt, notes[i]);
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

void
get_note(char str[NOTE_NAME_MAXLEN], int note, enum language lang) {
  enum { c0 = 4 }; // C0 is the first C and the fourth key in a 88-key piano.
  int octave_note = (note - c0) % OCTAVE; // FIXME: Corner case
                                          // when `(note - c0)` is negative.
  snprintf(str,
           NOTE_NAME_MAXLEN,
           "%s%u",
           note_names[lang][octave_note],
           ((note - c0) / OCTAVE) + 1);
}

void
cleanup(Sound *sounds[N_INSTRUMENTS][PIANO_KEYS]) {
  CloseWindow();
  StopSoundMulti();
  for (int i = 0; i < N_INSTRUMENTS; i++)
    for (int j = 0; j < PIANO_KEYS; j++)
      if (sounds[i][j]) {
        UnloadSound(*sounds[i][j]);
        free(sounds[i][j]);
      }
  CloseAudioDevice();
}

int
main() {
  int notes[HUMAN_FINGERS] = {0};
  int pressed[HUMAN_FINGERS] = {0};
  int pressed_once[HUMAN_FINGERS] = {0};
  Sound *sounds[N_INSTRUMENTS][PIANO_KEYS] = {0};
  const char *sound_file_fmts[N_INSTRUMENTS] = {
    "resources/sounds/piano-88-keys/%02d.mp3", NULL };
  enum item focused = PIANO;
  init();
  while (!WindowShouldClose()) {
    handle_input(pressed_once, pressed);
    switch (focused) {
    case PIANO:
    case GUITAR:
      for (int i = 0; i < HUMAN_FINGERS; i++) {
        notes[i] = key_to_note(pressed_once[i]);
        if (notes[i]) {
          char name[NOTE_NAME_MAXLEN];
          get_note(name, notes[i], PORTUGUESE);
          printf("%s ", name);
        }
      }
      if (notes[0]) {
        putchar('\n');
        play(notes, HUMAN_FINGERS, sounds[focused], sound_file_fmts[focused]);
      }
      // fall through
    default:
      draw();
    }
  }
  cleanup(sounds);
  return 0;
}
