#include <stdlib.h>
#include "musician.h"

// Static Function Declarations
MusicSequence* Play_Internal (Musician* musician, Score* score, SampleDefinition* sample);

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
MusicSequence* Play_Internal (Musician* musician, Score* score, SampleDefinition* sample)
{
  /*
  Tempo* tempo; 
  NoteSequence* notes;
  Instrument* instrument;
  MusicSequence* music;
  int noteLength, samplesPerTick, totalSamples;

  tempo = score->Tempo;
  notes = score->Notes;
  instrument = musician->Instrument;

  noteLength = notes->GetTickCount (notes);
  samplesPerTick = sample->SamplesPerSecond / tempo->TicksPerSecond;
  totalSamples = noteLength * samplesPerTick;

  music = BuildMusicSequence (totalSamples);
  instrument->SetNoteSource (instrument, (NoteSource*) score->Notes);

  while (music -> AddSample (music, instrument->PlaySample (instrument, tempo, sample)));
  return music;
  */
}
