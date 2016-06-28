#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "tempo.h"
#include "notesource.h"
#include "sampledefinition.h"
#include "periodgenerator.h"

typedef struct Instrument Instrument;

struct Instrument
{
  Note* CurrentNote;
  NoteSource* NoteSource;

  int CurrentSampleCount;
  Pitch CurrentPitch;
  Pitch PriorPitch;

  void (*SetNoteSource) (Instrument* instrument, NoteSource* NoteSource);
  int (*PlaySample) (Instrument* instrument, Tempo* tempo, SampleDefinition* sample);
};

Instrument* BuildInstrument();
void DestroyInstrument(Instrument* instrument);

#endif
