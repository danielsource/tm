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
