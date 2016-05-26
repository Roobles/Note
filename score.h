#ifndef SCORE_H
#define SCORE_H

#include "tempo.h"
#include "notesequence.h"

typedef struct
{
  Tempo* Tempo;
  NoteSequence* Notes;
} Score;

Score* BuildScore (Tempo* tempo, NoteSequence* sequence);
void DestroyScore (Score* score);
void PrintScore (Score* score);

#endif
