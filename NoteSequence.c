#include <stdlib.h>
#include "note.h"
#include "NoteSequence.h"

// Static Function Declarations
static Note* NextNote_Internal (NoteSequence* sequence);
static void AddNote_Internal (NoteSequence* sequence, Note* note);
static void Reset_Internal (NoteSequence* sequence);

// NoteSequence.h Implementation
NoteIttr* BuildNoteIttr(Note* note, NoteIttr* next)
{
  // TODO: Implement this.
  
  NoteIttr* ittr;

  ittr = malloc (sizeof (NoteIttr));
  ittr->Note = note;
  ittr->NextNote = next;

  return ittr;
}

void DestroyNoteIttr(NoteIttr* ittr)
{
  Note* note;
  NoteIttr *next;
  if(ittr == NULL)
    return;

  next = ittr->NextNote;

  if(next != NULL)
    DestroyNoteIttr(next);

  note = ittr->Note;
  DestroyNote(note);
  free (ittr);
}

NoteSequence* BuildNoteSequence()
{
  NoteSequence* sequence;
  
  sequence = malloc (sizeof (NoteSequence));
  sequence->Length = 0;
  sequence->IsConstructed = 1;

  sequence->CurrentNote = NULL;
  sequence->FirstNote = NULL;

  sequence->NextNote = NextNote_Internal;
  sequence->AddNote = AddNote_Internal;
  sequence->Reset = Reset_Internal;

  return sequence;
}

void DestroyNoteSequence(NoteSequence* sequence)
{
  NoteIttr* ittr;

  DestroyNoteIttr(sequence->FirstNote);

  sequence->Length = 0;
  sequence->IsConstructed = 0;

  sequence->CurrentNote = NULL;
  sequence->FirstNote = NULL;

  sequence->NextNote = NULL;
  sequence->AddNote = NULL;
  sequence->Reset = NULL;

  free (sequence);
}

// Static Function Implementations
static Note* NextNote_Internal (NoteSequence* sequence)
{
  NoteIttr** current;

  if(sequence == NULL || (current = &sequence->CurrentNote) == NULL || *current == NULL || sequence->FirstNote == NULL)
    return NULL;
  
  *current = (*current)->NextNote;
  return (*current == NULL)
    ? NULL
    : (*current)->Note;
}

static void AddNote_Internal (NoteSequence* sequence, Note* note)
{
}

static void Reset_Internal (NoteSequence* sequence)
{
}
