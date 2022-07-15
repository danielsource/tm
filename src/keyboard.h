#pragma once

void key2note(void);
void key2inputfield(void);

#define HUMAN_HAND_FINGERS 10
#define KEY2NOTE_MAX HUMAN_HAND_FINGERS
#define NOTE_NULL -1

struct key2note_buffer {
  int keys[KEY2NOTE_MAX];
  int notes[KEY2NOTE_MAX];
};
