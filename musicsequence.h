#ifndef MUSICSEQUENCE_H
#define MUSICSEQUENCE_H

#include "period.h"

typedef struct MusicSequence MusicSequence;
struct MusicSequence
{
  int* Samples;
  int Length;
  int Current;

  int (*AddSample) (MusicSequence* music, int sample);
  int (*AddPeriod) (MusicSequence* sequence, Period* period);
  void (*PrintDebug) (MusicSequence* music);
  double (*GetFrequency) (MusicSequence* music, int offset, int span, int spansPerSecond);
};

MusicSequence* BuildMusicSequence (int length);
void DestroyMusicSequence (MusicSequence* music);

#endif
