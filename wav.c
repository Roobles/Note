#include <stdlib.h>

#include "wav.h"
#include "string.h"

WavFile* BuildWavFile (char* name)
{
  WavFile* file;

  file = malloc (sizeof (WavFile));
  strncpy (file->Name, name, MAX_WAV_FILE_NAME);

  return file;
}

void DestroyWavFile(WavFile* file)
{
  strcpy (file->Name, "");
  free (file);
}
