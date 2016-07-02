#include <math.h>
#include <stdlib.h>
#include "periodgenerator.h"

static Period* GeneratePeriod_Internal (PeriodGenerator* generator, int frequency, int amplitude);
static int GeneratePeriodSample_Internal (PeriodGenerator* generator, int frequency, int amplitude, double offset, int i);

// PeriodGenerator.h Implementation
PeriodGenerator* BuildPeriodGenerator (PeriodAnalyzer* analyzer, SampleDefinition* definition)
{
  PeriodGenerator* generator;

  generator = malloc (sizeof (PeriodGenerator));
  generator->Analyzer = analyzer;
  generator->Definition = definition;
  generator->GeneratePeriod = GeneratePeriod_Internal;

  return generator;
}

void DestroyPeriodGenerator (PeriodGenerator* generator)
{
  if (generator == NULL) return;

  generator->Analyzer = NULL;
  generator->Definition = NULL;
  generator->GeneratePeriod = NULL;

  free (generator);
}

#
// Static Function Implementations
#define ExtractGeneratorComponents()                                                                                          \
  PeriodAnalyzer* analyzer;                                                                                                   \
  SampleDefinition* def;                                                                                                      \
                                                                                                                              \
  if (generator == NULL || (analyzer = generator->Analyzer) == NULL || (def = generator->Definition) == NULL) return 0x0 

static Period* GeneratePeriod_Internal (PeriodGenerator* generator, int frequency, int amplitude)
{
  int* samples;
  Period* period;
  double offset;
  int i, sampleCount, samplesPerSecond;
  
  ExtractGeneratorComponents();

  samplesPerSecond = def->SamplesPerSecond;
  sampleCount = analyzer->GetPeriodLength (frequency, samplesPerSecond);
  offset = ((double) 4 * (double) samplesPerSecond) / ((double) 5 * (double) frequency);
  
  samples = malloc (sizeof (int) * sampleCount);

  for(i=0; i<sampleCount; i++)
    samples[i] = GeneratePeriodSample_Internal (generator, frequency, amplitude, offset, i);

  period = BuildPeriod (frequency, amplitude, sampleCount, samples);
  free (samples);

  return period;
}

static int GeneratePeriodSample_Internal (PeriodGenerator* generator, int frequency, int amplitude, double offset, int i)
{
  unsigned int *currentSample;
  double value, radiansConv, sampleRate, sampleTick, periodRange;

  ExtractGeneratorComponents();

  sampleRate = (double) def->SamplesPerSecond;
  sampleTick = (double) i + offset;

  #define PI 3.14159265
  radiansConv = ((double) 2 * (double) PI) / (double) sampleRate;
  periodRange = (double) frequency * radiansConv;

  value = sin (periodRange * sampleTick);
  value *= (amplitude / 2);
  value += (amplitude / 2);

  return (int) value;
}
