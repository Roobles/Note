#include <stdlib.h>
#include "sampledefinition.h"

SampleDefinition* BuildSampleDefinition (unsigned int rate, unsigned int size)
{
  SampleDefinition* sample;

  sample = malloc (sizeof (SampleDefinition));
  sample->SamplesPerSecond = rate;
  sample->BitsPerSample = size;

  return sample;
}

void DestroySampleDefinition (SampleDefinition* sample)
{
  sample->SamplesPerSecond = 0x0;
  sample->BitsPerSample = 0x0;

  free (sample);
}
