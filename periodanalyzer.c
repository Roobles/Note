#include <stdlib.h>
#include <math.h>
#include "periodanalyzer.h"

#define PI 3.14159265
static int GetPeriodLength_Internal (int frequency, int sampleRate);

// PeriodAnalyzer.h Implementation
PeriodAnalyzer* BuildPeriodAnalyzer()
{
  PeriodAnalyzer* analyzer;
  
  analyzer = malloc (sizeof (PeriodAnalyzer));
  analyzer->GetPeriodLength = GetPeriodLength_Internal;

  return analyzer;
}

void DestroyPeriodAnalyzer(PeriodAnalyzer* analyzer)
{
  if (analyzer == NULL) return;

  analyzer->GetPeriodLength = NULL;
  free (analyzer);
}

// Static Function Implementations
static int GetPeriodLength_Internal (int frequency, int sampleRate)
{
  return (int) ceil ((double) sampleRate / (double) frequency);
}
