#ifndef NOTE_H
#define NOTE_H

#define TICK_SIZE 128

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
} Pitch;

typedef enum
{
  WholeNote = TICK_SIZE,
  HalfNote = TICK_SIZE / 2,
  QuarterNote = TICK_SIZE / 4,
  EigthNote = TICK_SIZE / 8,
  SixteenthNote = TICK_SIZE / 16
} NoteValue;

typedef struct Note Note;

struct Note
{
  Pitch Pitch;
  NoteValue Value;
  unsigned int Spent;

  int (*IsComplete) (Note* note);
  Pitch (*Tick) (Note* note);
};

Note* BuildNote(Pitch pitch, NoteValue value);
void DestroyNote(Note* note);

#endif
