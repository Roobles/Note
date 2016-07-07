#include <stdlib.h>
#include "musician.h"

// Static Function Declarations
MusicSequence* Play_Internal (Musician* musician, Score* score);

// Musician.h Implementation
Musician* BuildMusician (Instrument* instrument)
{
  Musician* musician;

  musician = malloc (sizeof (Musician));
  musician->Instrument = instrument;
  musician->Play = Play_Internal;

  return musician;
}

void DestroyMusician (Musician* musician)
{
  if (musician == NULL) return;  

  DestroyInstrument (musician->Instrument);
  musician->Play = NULL;
  
  free (musician);
}

// Static Function Implementations
MusicSequence* Play_Internal (Musician* musician, Score* score)
{
  Tempo* tempo; 
  NoteSequence* notes;
  SampleDefinition* definition;
  Instrument* instrument;
  MusicSequence* note, *composition = NULL;

  if (musician == NULL
    || score == NULL
    || (instrument = musician->Instrument) == NULL
    || (tempo = score->Tempo) == NULL
    || (notes = score->Notes) == NULL)
      return NULL;

  instrument->SetNoteSource (instrument, (NoteSource*) notes);
  while (note = instrument->PlayNote (instrument, tempo))
  {
    if (composition == NULL)
    {
      composition = note;
      continue;
    }

    composition = composition->Concat (composition, note);
  }
  
  return composition;
}
