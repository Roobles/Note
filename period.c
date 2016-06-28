#include <string.h>
#include <stdlib.h>
#include "period.h"

Period* BuildPeriod (int frequency, int amplitude, int length, const int* samples)
{
  Period* period;

  period = malloc (sizeof (Period));
  period->Frequency = frequency;
  period->Amplitude = amplitude;
  period->Length = length;
  
  period->Samples = malloc (sizeof (int) * length);
  memcpy (period->Samples, samples, sizeof (int));

  return period;
}

void DestroyPeriod (Period* period)
{
  if (period == NULL) return;

  free (period->Samples);
  free (period);
}
