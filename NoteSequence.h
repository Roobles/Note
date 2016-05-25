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
  struct NoteIttr* NextNote;
  struct NoteIttr* PriorNote;
};

struct NoteSequence
{
  NoteIttr* CurrentNote;
  NoteIttr* FirstNote;
  NoteIttr* LastNote;

  int Length;
  int IsConstructed;

  Note* (*NextNote) (NoteSequence* sequence);
  Note* (*PriorNote) (NoteSequence* sequence);
  void (*AddNote) (NoteSequence* sequence, Note* note);
  void (*Reset) (NoteSequence* sequence);
};

NoteIttr* BuildNoteIttr(Note* note, NoteIttr* prior, NoteIttr* next);
void DestroyNoteIttr(NoteIttr* ittr);

NoteSequence* BuildNoteSequence();
void DestroyNoteSequence(NoteSequence* sequence);

#endif
