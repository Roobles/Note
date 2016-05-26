#ifndef TEMPO_H
#define TEMPO_H

#include "note.h"

typedef struct
{
  unsigned int BeatsPerMinute;
  unsigned int TicksPerMinute;
  unsigned int TicksPerSecond;
  NoteValue BeatDefinition;
} Tempo;

Tempo* BuildTempo(unsigned int bpm, NoteValue definition);
void DestroyTempo(Tempo* tempo);

#endif
