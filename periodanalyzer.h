#ifndef PERIOD_ANALYZER_H
#define PERIOD_ANALYZER_H

typedef struct PeriodAnalyzer PeriodAnalyzer;

struct PeriodAnalyzer
{
  int (*GetPeriodLength) (int frequency, int sampleRate);
};

PeriodAnalyzer* BuildPeriodAnalyzer();
void DestroyPeriodAnalyzer(PeriodAnalyzer* analyzer);

#endif
