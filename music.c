#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

// Declarations
void BuildTestFile(WavFile** testFile);

// Main
int main (int argc, char** argv)
{

  WavFile* testFile;

  BuildTestFile(&testFile);
  printf ("Hello, world.\n");
  return 0;
}

// Functions
void BuildTestFile(WavFile** testFile)
{
  char* wavName = "TestName";
  *testFile = malloc (sizeof (WavFile));
  *testFile = BuildWavFile(wavName);
}

