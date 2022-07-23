#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "musical.h"

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
  if (!sound->frameCount) {
    free(sound);
    die("Sound file not found. Try executing inside the build directory.");
  }
  return sound;
}

void
get_note(char str[NOTE_NAME_MAXLEN], int note, enum language lang) {
  enum { c0 = 4 }; // C0 is the first C and the fourth key in a 88-key piano.
  int octave_note = (note - c0) % OCTAVE; // FIXME: Corner case
                                          // when `(note - c0)` is negative.
  snprintf(str, NOTE_NAME_MAXLEN,
           "%s%u", note_names[lang][octave_note],
           ((note - c0) / OCTAVE) + 1);
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
play_instrument(int keys[HUMAN_FINGERS], int notes[HUMAN_FINGERS],
                Sound *sounds[], const char *file_fmt) {
  int i, j;
  char name[NOTE_NAME_MAXLEN];
  for (i = j = 0; j < HUMAN_FINGERS; j++) {
    notes[i] = key_to_note(keys[j]);
    if (!notes[i])
      continue;
    if (!sounds[notes[i] - 1]) // We need to decrement by one
                               // because `notes` have 1-based indexing.
      sounds[notes[i] - 1] = get_sound(file_fmt, notes[i]);
    PlaySoundMulti(*sounds[notes[i] - 1]);
    get_note(name, notes[i], PORTUGUESE);
    printf("%s ", name);
    i++;
  }
  if (notes[0])
    putchar('\n');
}

void
draw(void) {
  BeginDrawing();
  ClearBackground(BLUE);
  EndDrawing();
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
      play_instrument(pressed_once, notes,
                      sounds[focused], sound_file_fmts[focused]);
      // fall through
    default:
      draw();
    }
  }
  cleanup(sounds);
  return 0;
}
