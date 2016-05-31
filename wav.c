#include <stdlib.h>
#include <string.h>

#include "wav.h"

WavFile* BuildWavFile(char* name, MusicSequence* music)
{
  WavFile* file;

  file = malloc (sizeof (WavFile));
  strncpy (file->Name, name, MAX_WAV_FILE_NAME);
  file->Music = music;

  return file;
}

void DestroyWavFile(WavFile* file)
{
  strcpy (file->Name, "");
  DestroyMusicSequence (file->Music);
  free (file);
}
