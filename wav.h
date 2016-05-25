#ifndef WAV_H
#define WAV_H

#include "score.h"

#define MAX_WAV_FILE_NAME 255


typedef struct
{
  char Name[MAX_WAV_FILE_NAME];
  Score* Score;
} WavFile;

WavFile* BuildWavFile(char* name);
void DestroyWavFile(WavFile* file);

#endif
