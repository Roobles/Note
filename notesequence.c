#include <stdlib.h>
#include "note.h"
#include "notesequence.h"

// Static Function Declarations
static Note* NextNote_Internal (NoteSequence* sequence);
static void AddNote_Internal (NoteSequence* sequence, Note* note);
static void Reset_Internal (NoteSequence* sequence);
static int GetTickCount_Internal (NoteSequence* sequence);

// notesequence.h Implementation
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

  ittr->NextNote = NULL;
  ittr->Note = NULL;
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
  sequence->AddNote = AddNote_Internal;
  sequence->Reset = Reset_Internal;
  sequence->GetTickCount = GetTickCount_Internal;

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
  sequence->AddNote = NULL;
  sequence->Reset = NULL;
  sequence->GetTickCount = NULL;

  free (sequence);
}

// Static Function Implementations
static Note* NextNote_Internal (NoteSequence* sequence)
{
  Note* note;
  NoteIttr** current;

  if(sequence == NULL || (current = &sequence->CurrentNote) == NULL || *current == NULL || sequence->FirstNote == NULL)
    return NULL;
  
  note = (*current)->Note;
  *current = (*current)->NextNote;
  
  return note;
}

static void AddNote_Internal (NoteSequence* sequence, Note* note)
{
  NoteIttr** last;
  NoteIttr* noteIttr;

  if (sequence == NULL || note == NULL)
    return;

  ++sequence->Length;
  noteIttr = BuildNoteIttr(note, NULL);

  // If this is the first note, set things up.
  if (sequence->FirstNote == NULL || sequence->CurrentNote == NULL || sequence->LastNote == NULL)
  {
    sequence->CurrentNote = sequence->FirstNote = sequence->LastNote = noteIttr;
    return;
  }

  // Other notes exist.
  last = &sequence->LastNote;
  (*last)->NextNote = noteIttr;
  *last = noteIttr;
}

static void Reset_Internal (NoteSequence* sequence)
{
  if (sequence == NULL || sequence->FirstNote == NULL)
    return;

  sequence->CurrentNote = sequence->FirstNote;
}

static int GetTickCount_Internal (NoteSequence* sequence)
{
  int tickCount;
  NoteIttr* note;
  
  tickCount = 0;
  if (sequence == NULL) return 0;

  note = sequence->FirstNote;
  while (note != NULL)
  {
    tickCount += note->Note->Value;
    note = note->NextNote;
  }
  
  return tickCount;
}
