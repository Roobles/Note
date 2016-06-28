#ifndef PERIOD_H
#define PERIOD_H

typedef struct Period Period;

struct Period
{
  int Frequency;
  int Amplitude;
  int Length;
  int* Samples;

  void (*DebugPrintPeriod) (Period* period);
};

Period* BuildPeriod (int frequency, int amplitude, int length, const int* samples);
void DestroyPeriod (Period* period);
#endif
