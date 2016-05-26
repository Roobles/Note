#include <stdlib.h>
#include <string.h>

#include "wav.h"

WavFile* BuildWavFile(char* name, Score* score)
{
  WavFile* file;

  file = malloc (sizeof (WavFile));
  strncpy (file->Name, name, MAX_WAV_FILE_NAME);
  file->Score = score;

  return file;
}

void DestroyWavFile(WavFile* file)
{
  strcpy (file->Name, "");
  DestroyScore (file->Score);
  free (file);
}
