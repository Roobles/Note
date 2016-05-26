#ifndef SCORE_H
#define SCORE_H

#include "note.h"
#include "notesequence.h"

typedef enum
{
  UnknownTempo = 0x0,
  Standard = 0x1
} Tempo;

typedef struct
{
  Tempo Tempo;
  NoteSequence* Notes;
} Score;

Score* BuildScore (Tempo tempo, NoteSequence* sequence);
void DestroyScore (Score* score);
void PrintScore (Score* score);

#endif
