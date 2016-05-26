#include<stdlib.h>
#include "note.h"

// Static Functions
static int IsComplete_Internal (Note* note);
static Notes Tick_Internal (Note* note);

// note.h Implementation
Note* BuildNote(Notes value, unsigned int duration)
{
  Note* note;

  note = malloc (sizeof (Note));
  note->Value = value;
  note->Duration = duration;
  note->Spent = 0x0;

  note->IsComplete = IsComplete_Internal;
  note->Tick = Tick_Internal;

  return note;
}

void DestroyNote(Note* note)
{
  note->Value = 0x0;
  note->Duration = 0x0;
  note->Spent = 0x0;

  note->IsComplete = NULL;
  note->Tick = NULL;

  free (note);
}

static int IsComplete_Internal (Note* note)
{
  return note == NULL || note->Spent >= note->Duration;
}

static Notes Tick_Internal (Note* note)
{
  if (note == NULL || note->IsComplete(note))
    return Rest;

  ++note->Spent;
  return note->Value;
}
