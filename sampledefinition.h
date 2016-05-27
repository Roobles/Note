#ifndef SAMPLEDEFINITION_H
#define SAMPLEDEFINITION_H

typedef struct
{
  unsigned int SamplesPerSecond;
  unsigned int BitsPerSample;
} SampleDefinition;

SampleDefinition* BuildSampleDefinition (unsigned int rate, unsigned int size);
void DestroySampleDefinition (SampleDefinition* sample);

#endif
