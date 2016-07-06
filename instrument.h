#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "tempo.h"
#include "notesource.h"
#include "musicsequence.h"
#include "sampledefinition.h"
#include "periodanalyzer.h"
#include "periodgenerator.h"

typedef struct Instrument Instrument;

struct Instrument
{
  Note* CurrentNote;
  NoteSource* NoteSource;
  SampleDefinition* SampleDefinition;
  PeriodAnalyzer* PeriodAnalyzer;
  PeriodGenerator* PeriodGenerator;

  void (*SetNoteSource) (Instrument* instrument, NoteSource* NoteSource);
  MusicSequence* (*PlayNote) (Instrument* instrument, Tempo* tempo);
};

Instrument* BuildInstrument(SampleDefinition* definition);
void DestroyInstrument(Instrument* instrument);

#endif
