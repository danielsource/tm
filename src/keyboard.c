#include <string.h>

#include "raylib.h"

#include "keyboard.h"
#include "main.h"
#include "util.h"

void key2note(void) {
  int changed = 0;
  memset(Ctx.pressed.keys, KEY_NULL, sizeof Ctx.pressed.keys);
  memset(Ctx.pressed.notes, NOTE_NULL, sizeof Ctx.pressed.notes);
  for (int key, note; (key = GetKeyPressed()) != KEY_NULL;) {
    switch (key) {
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
    default:        note = NOTE_NULL;
    }
    if (note == NOTE_NULL)
      break;
    for (int i=0; i<KEY2NOTE_MAX; i++) {
      if (Ctx.pressed.notes[i] == NOTE_NULL) {
        Ctx.pressed.notes[i] = note;
        Ctx.pressed.keys[i] = key;
        changed = 1;
        break;
      }
    }
  }
  for (int i=0; i<KEY2NOTE_MAX; i++) {
    if (Ctx.down.keys[i] != KEY_NULL &&
        !IsKeyDown(Ctx.down.keys[i])) {
      Ctx.down.notes[i] = NOTE_NULL;
      Ctx.down.keys[i] = KEY_NULL;
      changed = 1;
    }
  }
  for (int i=0, j=0; i<KEY2NOTE_MAX; i++) {
    if (Ctx.pressed.keys[j] == KEY_NULL)
      break;
    if (Ctx.down.keys[i] != KEY_NULL)
      continue;
    Ctx.down.notes[i] = Ctx.pressed.notes[j];
    Ctx.down.keys[i] = Ctx.pressed.keys[j];
    j++;
    changed = 1;
  }
  if (changed) {
    LOGINFO("pressed:", 0);
    LOGINFO_ARR(Ctx.pressed.notes, KEY2NOTE_MAX, "\tnotes: ", "%2d ");
    LOGINFO_ARR(Ctx.pressed.keys, KEY2NOTE_MAX, "\tkeys : ", "%2d ");
    LOGINFO("down:", 0);
    LOGINFO_ARR(Ctx.down.notes, KEY2NOTE_MAX, "\tnotes: ", "%2d ");
    LOGINFO_ARR(Ctx.down.keys, KEY2NOTE_MAX, "\tkeys : ", "%2d ");
  }
}

void key2inputfield(void) {
  struct inputfield *f = &Ctx.elements[INPUTFIELD].u.inputfield;
  if (!f->text[0]) {
    strncpy(f->text, "Type stuff", MAX(11, INPUTFIELD_TEXT_MAX));
    LOGINFO("input field initialized", 0);
  }
}
