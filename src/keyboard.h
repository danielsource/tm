#pragma once

#define HUMAN_HAND_FINGERS 10
#define KEY2NOTE_MAX HUMAN_HAND_FINGERS
#define NOTE_NULL -1
struct key2note_buffer {
  int keys[KEY2NOTE_MAX];
  int notes[KEY2NOTE_MAX];
};

#define INPUTFIELD_TEXT_MAX 64
struct inputfield {
  int count;
  char text[INPUTFIELD_TEXT_MAX];
};

void key2note(void);
void key2inputfield(void);
