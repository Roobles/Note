#ifndef NOTESOURCE_H
#define NOTESOURCE_H

typedef struct NoteSource NoteSource;

struct NoteSource
{
  Note* (*NextNote) (NoteSource* source);
};
#endif
