#ifndef MUSICSEQUENCE_H
#define MUSICSEQUENCE_H

typedef struct MusicSequence MusicSequence;
struct MusicSequence
{
  int* Samples;
  int Length;
  int Current;

  int (*AddSample) (MusicSequence* music, int sample);
  void (*PrintDebug) (MusicSequence* music);
};

MusicSequence* BuildMusicSequence (int length);
void DestroyMusicSequence (MusicSequence* music);

#endif
