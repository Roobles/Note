#include <stdlib.h>
#include <math.h>
#include "instrument.h"
#include "periodgenerator.h"
#include "periodanalyzer.h"

// Static Function Declarations
static void SetNoteSource_Internal (Instrument* instrument, NoteSource* NoteSource);
static Note* GetCurrentInstrumentNote_Internal (Instrument* instrument);
static MusicSequence* PlayNote_Internal (Instrument* instrument, Tempo* tempo);
static MusicSequence* PlayRest_Internal (Instrument* instrument, Tempo* tempo, Note* note);
static MusicSequence* PlayNoteValue_Internal (Instrument* instrument, Tempo* tempo, Note* note);
static int GetPeriodsPerNote_Internal (Instrument* instrument, Note* note, Tempo* tempo, int periodLength);

// instrument.h Implementation
Instrument* BuildInstrument(SampleDefinition* definition)
{
  Instrument* instrument;
  PeriodAnalyzer* analyzer;
  
  analyzer = BuildPeriodAnalyzer ();
  instrument = malloc (sizeof (Instrument));
  instrument->CurrentNote = NULL;
  instrument->NoteSource = NULL;

  instrument->SampleDefinition = definition;
  instrument->PeriodAnalyzer = analyzer;
  instrument->PeriodGenerator = BuildPeriodGenerator (analyzer, definition);

  instrument->SetNoteSource = SetNoteSource_Internal;
  instrument->PlayNote = PlayNote_Internal;

  return instrument;
}

void DestroyInstrument(Instrument* instrument)
{
  instrument->CurrentNote = NULL;
  instrument->NoteSource = NULL;

  instrument->SampleDefinition = NULL;
  DestroyPeriodGenerator (instrument->PeriodGenerator);
  DestroyPeriodAnalyzer (instrument->PeriodAnalyzer);

  instrument->SetNoteSource = NULL;
  instrument->PlayNote = NULL;

  free (instrument);
}

// Static Function Implementations
static void SetNoteSource_Internal (Instrument* instrument, NoteSource* NoteSource)
{
  if(instrument == NULL) return;

  instrument->NoteSource = NoteSource;
}

static MusicSequence* PlayNote_Internal (Instrument* instrument, Tempo* tempo)
{
  Period* period;
  Note* note;
  Pitch pitch;
  MusicSequence* (*play) (Instrument* instrument, Tempo* tempo, Note* note);

  if (instrument == NULL || (note = GetCurrentInstrumentNote_Internal (instrument)) == NULL) 
    return NULL;

  play = note->Pitch == Rest
    ? PlayRest_Internal
    : PlayNoteValue_Internal;

  return play (instrument, tempo, note);
}

static MusicSequence* PlayRest_Internal (Instrument* instrument, Tempo* tempo, Note* note)
{
  SampleDefinition* definition;
  int i, sampleCount, samplesPerSecond, ticksPerSecond, ticks;  
  MusicSequence* sequence;

  if (instrument == NULL
    || tempo == NULL
    || note == NULL
    || (definition = instrument->SampleDefinition) == NULL)
      return NULL;
  
  ticks = note->Value;
  samplesPerSecond = definition->SamplesPerSecond;
  ticksPerSecond = tempo->TicksPerSecond;

  sampleCount = (samplesPerSecond * ticks) / ticksPerSecond;
  sequence = BuildMusicSequence (sampleCount);
  for (i=0; i<sampleCount; i++)
    sequence->AddSample (sequence, 0);

  return sequence;
}

static MusicSequence* PlayNoteValue_Internal (Instrument* instrument, Tempo* tempo, Note* note)
{
  int i;
  Period* period;
  double sampleDepth;
  MusicSequence* sequence;
  PeriodGenerator* generator;
  PeriodAnalyzer* analyzer;
  SampleDefinition* definition;
  unsigned int frequency, amplitude, sampleRate, sampleLength,
    periodLength, totalPeriods, sequenceLength;

  if (instrument == NULL
    || tempo == NULL
    || note == NULL
    || (generator = instrument->PeriodGenerator) == NULL
    || (analyzer = instrument->PeriodAnalyzer) == NULL
    || (definition = instrument->SampleDefinition) == NULL)
      return NULL;

  frequency = note->Pitch;
  sampleRate = definition->SamplesPerSecond;
  sampleDepth = (double) (pow (2, definition->BitsPerSample) - 1);

  // TODO: Be wicked smahter about this.
  amplitude = floor (sampleDepth) / 2;

  periodLength = analyzer->GetPeriodLength (frequency, sampleRate);
  totalPeriods = GetPeriodsPerNote_Internal (instrument, note, tempo, periodLength);
  sequenceLength = periodLength * totalPeriods;
  sequence = BuildMusicSequence (sequenceLength);

  for (i=0; i<totalPeriods; i++)
  {
    // TODO: Be wicked smahter about this.
    period = generator->GeneratePeriod (generator, frequency, amplitude);
    sequence->AddPeriod (sequence, period);
    DestroyPeriod (period);
  }

  return sequence;
}

static Note* GetCurrentInstrumentNote_Internal (Instrument* instrument)
{
  Note* targetNote, **cNote;
  NoteSource* source;

  if (instrument == NULL
    || (source = instrument->NoteSource) == NULL)
      return NULL;

  return source->NextNote (source);
}

static int GetPeriodsPerNote_Internal (Instrument* instrument, Note* note, Tempo* tempo, int periodLength)
{
  PeriodAnalyzer* analyzer;
  SampleDefinition* definition;
  Pitch pitch;
  int sampleRate, totalTicks,
    ticksPerSecond, samplesPerTick;

  if (instrument == NULL 
    || note == NULL
    || tempo == NULL
    || (definition = instrument->SampleDefinition) == NULL
    || (pitch = note->Pitch) == Rest)
        return 0; 

  sampleRate = definition->SamplesPerSecond;
  totalTicks = note->Value;
  ticksPerSecond = tempo->TicksPerSecond;
  return (totalTicks * sampleRate) / (ticksPerSecond * periodLength);
}
