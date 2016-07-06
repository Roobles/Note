#include <stdlib.h>
#include <stdio.h>
#include "musicsequence.h"

// Static Function Declarations
static int AddSample_Internal (MusicSequence* music, int sample);
static int AddPeriod_Internal (MusicSequence* sequence, Period* period);
static void PrintDebug_Internal (MusicSequence* music);
static double GetFrequency_Internal (MusicSequence* music, int offset, int span, int spansPerSecond);

// MusicSequence.h Implementation
MusicSequence* BuildMusicSequence (int length)
{
  MusicSequence* music;

  music = malloc (sizeof (MusicSequence));
  music->Length = length;
  music->Current = 0;
  music->Samples = malloc (sizeof (int) * length);

  music->AddSample = AddSample_Internal;
  music->AddPeriod = AddPeriod_Internal;
  music->PrintDebug = PrintDebug_Internal;
  music->GetFrequency = GetFrequency_Internal;

  return music;
}

void DestroyMusicSequence (MusicSequence* music)
{
  if (music == NULL) return;

  music->Length = 0; 
  music->Current = 0;
  music->AddSample = NULL;
  music->AddPeriod = NULL;
  music->PrintDebug = NULL;
  music->GetFrequency = NULL;

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

static int AddPeriod_Internal (MusicSequence* sequence, Period* period)
{  
  int i, periodLength, sample, *samples,
    current = 0;

  if (sequence == NULL
    || period == NULL
    || (samples = period->Samples) == NULL
    || (periodLength = period->Length) <= 0)
      return 0;

  for (i=0; i<periodLength; i++)
    current = AddSample_Internal (sequence, samples[i]);
  
  return current;
}

static void PrintDebug_Internal (MusicSequence* music)
{
  int i, current, sample;
  if (music == NULL) return; 

  current = music->Current;
  for (i=0; i<current; i++)
    printf ("[Sequence %05d]: %d\n", i+1, music->Samples[i]);
}

static double GetFrequency_Internal (MusicSequence* music, int offset, int span, int spansPerSecond)
{
  int* samples; 
  int i, ticks, currentSample, priorSample,
    currentSlope, priorSlope;

  samples = music->Samples + offset;
  for (i=ticks=priorSlope=currentSample=0; i<span; i++)
  {
    priorSample = currentSample;
    currentSample = samples[i];
    currentSlope = priorSample > currentSample
      ? 1
      : priorSample == currentSample
        ? 0
        : -1;

    if (currentSlope != priorSlope && currentSlope < 0)
      ++ticks;

    priorSlope = currentSlope;
  }

  return (double)ticks / (double) spansPerSecond;
}
