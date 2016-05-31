#include <stdlib.h>
#include <stdio.h>
#include "musicsequence.h"

// Static Function Declarations
static int AddSample_Internal (MusicSequence* music, int sample);
static void PrintDebug_Internal (MusicSequence* music);

// MusicSequence.h Implementation
MusicSequence* BuildMusicSequence (int length)
{
  MusicSequence* music;

  music = malloc (sizeof (MusicSequence));
  music->Length = length;
  music->Current = 0;
  music->Samples = malloc (sizeof (int) * length);

  music->AddSample = AddSample_Internal;
  music->PrintDebug = PrintDebug_Internal;

  return music;
}

void DestroyMusicSequence (MusicSequence* music)
{
  if (music == NULL) return;

  music->Length = 0; 
  music->Current = 0;
  music->AddSample = NULL;

  free (music->Samples);
  free (music);
}

// Static Function Implementations
static int AddSample_Internal (MusicSequence* music, int sample)
{
  int *length, *current;
  if (music == NULL || *(current = &music->Current) >= *(length = &music->Length))
    return 0;

  music->Samples[(*current)++] = sample;
  return *current;
}

static void PrintDebug_Internal (MusicSequence* music)
{
  int i, current, sample;
  if (music == NULL) return; 

  current = music->Current;
  for (i=0; i<current; i++)
    printf ("[Sequence %05d]: %d\n", i+1, music->Samples[i]);
}
