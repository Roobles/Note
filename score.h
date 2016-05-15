#ifndef SCORE_H
#define SCORE_H

#include "note.h"
#include "NoteSequence.h"

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

NoteSequence* BuildScore (Tempo tempo, Score* score);

#endif
