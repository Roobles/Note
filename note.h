#ifndef NOTE_H
#define NOTE_H

typedef enum
{
  UnknownNote = 0x0,
  Rest = 0x1,
  A = 0x2,
  B = 0x3,
  C = 0x4,
  D = 0x5,
  E = 0x6,
  F = 0x7,
  G = 0x8
} Notes;

typedef struct Note Note;

struct Note
{
  Notes Value;
  unsigned int Duration;
  unsigned int Spent;

  int (*IsComplete) (Note* note);
  Notes (*Tick) (Note* note);
};

Note* BuildNote(Notes value, unsigned int duration);
void DestroyNote(Note* note);

#endif
