#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "period.h"

static void DebugPrintPeriod_Internal (Period* period);

// Period.h Implementation
Period* BuildPeriod (int frequency, int amplitude, int length, const int* samples)
{
  Period* period;
  int samplesSize;

  period = malloc (sizeof (Period));
  period->Frequency = frequency;
  period->Amplitude = amplitude;
  period->Length = length;

  period->DebugPrintPeriod = DebugPrintPeriod_Internal; 
  
  samplesSize = sizeof (int) * length;
  period->Samples = malloc (samplesSize);
  memcpy (period->Samples, samples, samplesSize);

  return period;
}

void DestroyPeriod (Period* period)
{
  if (period == NULL) return;

  period->Frequency = 0x0;
  period->Amplitude = 0x0;
  period->Length = 0x0;

  period->DebugPrintPeriod = NULL;

  free (period->Samples);
  free (period);
}

// Static Function Implementations
static void DebugPrintPeriod_Internal (Period* period)
{
  int *samples, len, i;
  if (period == NULL) return;

  len = period->Length;
  samples = period->Samples;
  
  for (i=0; i<len; i++)
    printf("Sample %3d: %6d\n", i, samples[i]); 
}
