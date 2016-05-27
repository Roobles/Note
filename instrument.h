#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "note.h"
#include "notesource.h"

typedef struct Instrument Instrument;

struct Instrument
{
  Note* CurrentNote;
  NoteSource* NoteSource;

  void (*SetNoteSource) (Instrument* instrument, NoteSource* NoteSource);
  int (*PlayTick) (Instrument* instrument);
};

Instrument* BuildInstrument();
void DestroyInstrument(Instrument* instrument);

#endif
