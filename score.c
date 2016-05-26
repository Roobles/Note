#include <stdlib.h>
#include <stdio.h>
#include "score.h"

Score* BuildScore (Tempo tempo, NoteSequence* sequence)
{
  Score* score;

  score = malloc (sizeof (Score));
  score->Tempo = tempo;
  score->Notes = sequence;
}


void DestroyScore (Score* score)
{
  if (score == NULL) return;
  score->Tempo = 0x0;
  DestroyNoteSequence (score->Notes);
  free (score);
}

void PrintScore (Score* score)
{
  NoteSequence* seq;
  Note* note;

  if (score == NULL || (seq = score->Notes) == NULL || seq->Length < 1)
    return;

  seq->Reset (seq);
  for (note = seq->NextNote(seq); note != NULL; note = seq->NextNote(seq))
    printf ("Note: %d  Duration: %d\n", note->Value, note->Duration);
  
}
