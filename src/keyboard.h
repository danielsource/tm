#pragma once

#define HUMAN_HAND_FINGERS 10
#define KEYBOARD_KEYS_MAX HUMAN_HAND_FINGERS
#define NOTE_NULL -1
struct key2note_buffer {
  int keys[KEYBOARD_KEYS_MAX];
  int notes[KEYBOARD_KEYS_MAX];
};

#define INPUTFIELD_TEXT_MAX 64
struct inputfield {
  int count;
  char text[INPUTFIELD_TEXT_MAX];
};

void key2note(void);
void key2inputfield(void);
int lookup_note(int);
