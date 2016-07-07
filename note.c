#include<stdlib.h>
#include "note.h"

// note.h Implementation
Note* BuildNote(Pitch pitch, NoteValue value)
{
  Note* note;

  note = malloc (sizeof (Note));
  note->Pitch = pitch;
  note->Value = value;

  return note;
}

void DestroyNote(Note* note)
{
  note->Value = 0x0;
  note->Pitch = 0x0;

  free (note);
}
