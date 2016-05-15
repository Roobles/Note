#include "wav.h"
#include "string.h"

int BuildWavFile(char* name, WavFile* file)
{
  strncpy (file->Name, name, MAX_WAV_FILE_NAME);
  return 0;
}

int DestroyWavFile(WavFile* file)
{
  strcpy (file->Name, "");
  return 0;
}
