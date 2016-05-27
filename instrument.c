#include <stdlib.h>
#include "instrument.h"

// Static Function Declarations
static void SetNoteSource_Internal (Instrument* instrument, NoteSource* NoteSource);
static Note* GetCurrentInstrumentNote_Internal (Instrument* instrument);
static int PlayTick_Internal (Instrument* instrument);

// instrument.h Implementation
Instrument* BuildInstrument()
{
  Instrument* instrument;
  
  instrument = malloc (sizeof (Instrument));
  instrument->CurrentNote = NULL;
  instrument->NoteSource = NULL;

  instrument->SetNoteSource = SetNoteSource_Internal;
  instrument->PlayTick = PlayTick_Internal;

  return instrument;
}

void DestroyInstrument(Instrument* instrument)
{
  instrument->CurrentNote = NULL;
  instrument->NoteSource = NULL;
  instrument->SetNoteSource = NULL;
  instrument->PlayTick = NULL;

  free (instrument);
}

// Static Function Implementations
static void SetNoteSource_Internal (Instrument* instrument, NoteSource* NoteSource)
{
  if(instrument == NULL) return;

  instrument->NoteSource = NoteSource;
}

static int PlayTick_Internal (Instrument* instrument)
{
  Note* note;
  Pitch tickPitch;
  
  note = GetCurrentInstrumentNote_Internal (instrument);
  tickPitch = note->Tick (note);
}

static Note* GetCurrentInstrumentNote_Internal (Instrument* instrument)
{
  Note* targetNote, **cNote;
  NoteSource* nSource;

  if (instrument == NULL) return 0;

  cNote = &instrument->CurrentNote;
  nSource = instrument->NoteSource;

  targetNote = (*cNote == NULL || (*cNote)->IsComplete (*cNote))
    ? nSource->NextNote (nSource)
    : *cNote;

  if(*cNote != targetNote)
    *cNote = targetNote;

  return targetNote;
}
