#include <stdlib.h>
#include "tempo.h"

Tempo* BuildTempo(unsigned int bpm, NoteValue definition)
{
  Tempo* tempo;

  tempo = malloc (sizeof (Tempo));
  tempo->BeatsPerMinute = bpm;
  tempo->BeatDefinition = definition;
  tempo->TicksPerMinute = (bpm * definition);
  tempo->TicksPerSecond = (tempo->TicksPerMinute / 60);

  return tempo;
}

void DestroyTempo(Tempo* tempo)
{
  if (tempo == NULL) return;

  tempo->BeatsPerMinute = 0x0;
  tempo->BeatDefinition = 0x0;

  free (tempo);
}
