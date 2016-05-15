#ifndef WAV_H
#define WAV_H

#include "score.h"

#define MAX_WAV_FILE_NAME 255


typedef struct
{
  char Name[MAX_WAV_FILE_NAME];
  Score* Score;
} WavFile;

int BuildWavFile(char* name, WavFile* file);
int DestroyWavFile(WavFile* file);

#endif
