#include <string.h>

#include "raylib.h"

#include "keyboard.h"
#include "main.h"
#include "util.h"

void
key2note(void) {
  static int changed = -1;
  if (changed == -1) {
    memset(Ctx.down.keys, KEY_NULL, sizeof Ctx.down.keys);
    memset(Ctx.down.notes, NOTE_NULL, sizeof Ctx.down.notes);
  }
  if (changed) {
    memset(Ctx.pressed.keys, KEY_NULL, sizeof Ctx.pressed.keys);
    memset(Ctx.pressed.notes, NOTE_NULL, sizeof Ctx.pressed.notes);
    changed = 0;
    LOGINFO("memset in Ctx.pressed", 0);
  }
  for (int key, note; (key = GetKeyPressed()) != KEY_NULL;) {
    if ((note = lookup_note(key)) == NOTE_NULL)
      break;
    for (int i=0; i<KEYBOARD_KEYS_MAX; i++)
      if (Ctx.pressed.notes[i] == NOTE_NULL) {
        Ctx.pressed.notes[i] = note;
        Ctx.pressed.keys[i] = key;
        changed = 1;
        break;
      }
  }
  for (int i=0; i<KEYBOARD_KEYS_MAX; i++)
    if (Ctx.down.keys[i] != KEY_NULL &&
        !IsKeyDown(Ctx.down.keys[i])) {
      Ctx.down.notes[i] = NOTE_NULL;
      Ctx.down.keys[i] = KEY_NULL;
      changed = 1;
    }
  for (int i=0, j=0; i<KEYBOARD_KEYS_MAX; i++) {
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
    LOGINFO_ARR(Ctx.pressed.notes, KEYBOARD_KEYS_MAX, "\tnotes: ", "%2d ");
    LOGINFO_ARR(Ctx.pressed.keys, KEYBOARD_KEYS_MAX, "\tkeys : ", "%2d ");
    LOGINFO("down:", 0);
    LOGINFO_ARR(Ctx.down.notes, KEYBOARD_KEYS_MAX, "\tnotes: ", "%2d ");
    LOGINFO_ARR(Ctx.down.keys, KEYBOARD_KEYS_MAX, "\tkeys : ", "%2d ");
  }
}

void
key2inputfield(void) {
  struct inputfield *f = &Ctx.elements[INPUTFIELD].u.inputfield;
  if (!f->text[0]) {
    strncpy(f->text, "Type stuff", MAX(11, INPUTFIELD_TEXT_MAX));
    LOGINFO("input field initialized", 0);
  }
}

int
lookup_note(int key) {
  switch (key) {
  case KEY_Q:     return 24; // 24 is C3,
  case KEY_TWO:   return 25; // 25 is C#3,
  case KEY_W:     return 26; // 26 is D3, and so on.
  case KEY_THREE: return 27;
  case KEY_E:     return 28;
  case KEY_R:     return 29;
  case KEY_FIVE:  return 30;
  case KEY_T:     return 31;
  case KEY_SIX:   return 32;
  case KEY_Y:     return 33;
  case KEY_SEVEN: return 34;
  case KEY_U:     return 35;
  case KEY_I:
  case KEY_Z:     return 36;
  case KEY_S:     return 37;
  case KEY_X:     return 38;
  case KEY_D:     return 39;
  case KEY_C:     return 40;
  case KEY_V:     return 41;
  case KEY_G:     return 42;
  case KEY_B:     return 43;
  case KEY_H:     return 44;
  case KEY_N:     return 45;
  case KEY_J:     return 46;
  case KEY_M:     return 47;
  case KEY_COMMA: return 48;
  default:        return NOTE_NULL;
  }
}
