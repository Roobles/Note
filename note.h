#ifndef NOTE_H
#define NOTE_H

#define TICK_SIZE 128

typedef enum
{
  UnknownNote = 0x0,
  Rest = 0x1,
  A = 220,
  B = 247,
  C = 261,
  D = 293,
  E = 329,
  F = 349,
  G = 392
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
  void (*Reset) (Note* note);
};

Note* BuildNote(Pitch pitch, NoteValue value);
void DestroyNote(Note* note);

#endif
