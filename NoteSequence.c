#include <stdlib.h>
#include "note.h"
#include "NoteSequence.h"

// Static Function Declarations
static Note* NextNote_Internal (NoteSequence* sequence);
static Note* PriorNote_Internal (NoteSequence* sequence);
static void AddNote_Internal (NoteSequence* sequence, Note* note);
static void Reset_Internal (NoteSequence* sequence);

// NoteSequence.h Implementation
NoteIttr* BuildNoteIttr(Note* note, NoteIttr* prior, NoteIttr* next)
{
  // TODO: Implement this.
  
  NoteIttr* ittr;

  ittr = malloc (sizeof (NoteIttr));
  ittr->Note = note;
  ittr->NextNote = next;
  ittr->PriorNote = prior;

  return ittr;
}

void DestroyNoteIttr(NoteIttr* ittr)
{
  Note* note;
  struct NoteIttr *next, *prior;
  if(ittr == NULL)
    return;

  next = ittr->NextNote;
  prior = ittr->PriorNote;

  if(next != NULL)
    DestroyNoteIttr(next);

  note = ittr->Note;
  
  if (next != NULL) free (next);
  if (prior != NULL) free (prior);

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
  sequence->LastNote = NULL;

  sequence->NextNote = NextNote_Internal;
  sequence->PriorNote = PriorNote_Internal;
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
  sequence->LastNote = NULL;

  sequence->NextNote = NULL;
  sequence->PriorNote = NULL;
  sequence->AddNote = NULL;
  sequence->Reset = NULL;

  free (sequence);
}

// Static Function Implementations
static Note* NextNote_Internal (NoteSequence* sequence)
{
  NoteIttr** current;
  *current = sequence->CurrentNote;
  if(*current == NULL || sequence->FirstNote == NULL || sequence->LastNote == NULL)
    return NULL;
  
  return NULL;
}

static Note* PriorNote_Internal (NoteSequence* sequence)
{
}

static void AddNote_Internal (NoteSequence* sequence, Note* note)
{
}

static void Reset_Internal (NoteSequence* sequence)
{
}
