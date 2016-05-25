#ifndef NOTE_H
#define NOTE_H

typedef enum
{
  UnknownNote = 0x0,
  A = 0x1,
  B = 0x2,
  C = 0x3,
  D = 0x4,
  E = 0x5,
  F = 0x6,
  G = 0x7
} Notes;

typedef struct
{
  Notes Value;
  unsigned int Duration;
} Note;

Note* BuildNote(Notes value, unsigned int duration);
void DestroyNote(Note* note);

#endif
