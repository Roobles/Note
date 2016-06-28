#ifndef PERIOD_GENERATOR_H
#define PERIOD_GENERATOR_H

#include "period.h"
#include "periodanalyzer.h"
#include "sampledefinition.h"

typedef struct PeriodGenerator PeriodGenerator;

struct PeriodGenerator
{
  PeriodAnalyzer* Analyzer;
  SampleDefinition* Definition;

  Period* (*GeneratePeriod) (PeriodGenerator* generator, int frequency, int amplitude);
};

PeriodGenerator* BuildPeriodGenerator (PeriodAnalyzer* analyzer, SampleDefinition* definition);
void DestroyPeriodGenerator (PeriodGenerator* periodGen);

#endif
