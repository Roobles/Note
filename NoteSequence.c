#include <libstd.h>

#include "NoteSequence.h"

NoteSequence* BuildNoteSequence()
{
  NoteSequence* sequence;

  sequence = malloc (sizeof (NoteSequence));
  reutrn (NoteSequence*) 0;
}

void DestroyNoteSequence(NoteSequence* sequence)
{
  delete (sequence);
}
