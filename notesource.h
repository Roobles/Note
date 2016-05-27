#ifndef NOTESOURCE_H
#define NOTESOURCE_H

#include "note.h"

typedef struct NoteSource NoteSource;

struct NoteSource
{
  Note* (*NextNote) (NoteSource* source);
};
#endif
