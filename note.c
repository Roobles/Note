#include<stdlib.h>
#include "note.h"

Note* BuildNote(Notes value, unsigned int duration)
{
  Note* note;

  note = malloc (sizeof (Note));
  note->Value = value;
  note->Duration = duration;

  return note;
}

void DestroyNote(Note* note)
{
  note->Value = 0x0;
  note->Duration = 0x0;

  free (note);
}
