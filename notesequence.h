#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include "note.h"

struct NoteSequence;
struct NoteIttr;

typedef struct NoteIttr NoteIttr;
typedef struct NoteSequence NoteSequence;

struct NoteIttr
{
  Note* Note;
  NoteIttr* NextNote;
};

struct NoteSequence
{
  Note* (*NextNote) (NoteSequence* sequence);

  NoteIttr* CurrentNote;
  NoteIttr* FirstNote;
  NoteIttr* LastNote;

  int Length;
  int IsConstructed;

  void (*AddNote) (NoteSequence* sequence, Note* note);
  void (*Reset) (NoteSequence* sequence);
  int (*GetTickCount) (NoteSequence* sequence);
};

NoteIttr* BuildNoteIttr(Note* note, NoteIttr* next);
void DestroyNoteIttr(NoteIttr* ittr);

NoteSequence* BuildNoteSequence();
void DestroyNoteSequence(NoteSequence* sequence);

#endif
