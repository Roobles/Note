#include<stdlib.h>
#include "note.h"

// Static Functions
static int IsComplete_Internal (Note* note);
static Pitch Tick_Internal (Note* note);
static void Reset_Internal (Note* note);

// note.h Implementation
Note* BuildNote(Pitch pitch, NoteValue value)
{
  Note* note;

  note = malloc (sizeof (Note));
  note->Pitch = pitch;
  note->Value = value;
  note->Spent = 0x0;

  note->IsComplete = IsComplete_Internal;
  note->Tick = Tick_Internal;
  note->Reset = Reset_Internal;

  return note;
}

void DestroyNote(Note* note)
{
  note->Value = 0x0;
  note->Pitch = 0x0;
  note->Spent = 0x0;

  note->IsComplete = NULL;
  note->Tick = NULL;
  note->Reset = NULL;

  free (note);
}

static int IsComplete_Internal (Note* note)
{
  return note == NULL || note->Spent >= note->Value;
}

static Pitch Tick_Internal (Note* note)
{
  if (note == NULL || note->IsComplete(note))
    return Rest;

  ++note->Spent;
  return note->Pitch;
}

static void Reset_Internal (Note* note)
{
  if (note == NULL) return;

  note->Spent = 0x0;
}
