#include <stdlib.h>
#include <math.h>
#include "instrument.h"

// Static Function Declarations
static void SetNoteSource_Internal (Instrument* instrument, NoteSource* NoteSource);
static Note* GetCurrentInstrumentNote_Internal (Instrument* instrument);
static int PlaySample_Internal (Instrument* instrument, Tempo* tempo, SampleDefinition* sample);
static Pitch GetCurrentInstrumentPitch_Internal (Instrument* instrument, Tempo* tempo, SampleDefinition* sample);
static int GetSamplesPerTick_Internal (Tempo* tempo, SampleDefinition* sample);

// instrument.h Implementation
Instrument* BuildInstrument()
{
  Instrument* instrument;
  
  instrument = malloc (sizeof (Instrument));
  instrument->CurrentNote = NULL;
  instrument->NoteSource = NULL;

  instrument->CurrentPitch = UnknownNote;
  instrument->CurrentSampleCount = 0;

  instrument->SetNoteSource = SetNoteSource_Internal;
  instrument->PlaySample = PlaySample_Internal;

  return instrument;
}

void DestroyInstrument(Instrument* instrument)
{
  instrument->CurrentNote = NULL;
  instrument->NoteSource = NULL;

  instrument->CurrentPitch = UnknownNote;
  instrument->CurrentSampleCount = 0;

  instrument->SetNoteSource = NULL;
  instrument->PlaySample = NULL;

  free (instrument);
}

// Static Function Implementations
static void SetNoteSource_Internal (Instrument* instrument, NoteSource* NoteSource)
{
  if(instrument == NULL) return;

  instrument->NoteSource = NoteSource;
}

static int PlaySample_Internal (Instrument* instrument, Tempo* tempo, SampleDefinition* sample)
{
  Pitch samplePitch;
  int *currentSample;
  double value, frequency, volPercent, radiansConv,
    sampleRate, sampleDepth, sampleTick;

  sampleRate = (double) sample->SamplesPerSecond;
  sampleDepth = (double) (pow (2, sample->BitsPerSample) - 1);
  volPercent = (double) .5;

  currentSample = &instrument->CurrentSampleCount;
  samplePitch = GetCurrentInstrumentPitch_Internal (instrument, tempo, sample);
  frequency = (double) samplePitch;
  sampleTick = (double) *currentSample;

  #define PI 3.14159265
  radiansConv = (double) PI / (double) 180;
  value = sin (sampleTick * radiansConv);
  value = (value * sampleDepth) / 2;
  value += (sampleDepth / 2);

  value = floor (sin (22 * sampleTick * radiansConv) * (sampleDepth / 2));
  value += (sampleDepth / 2);
  value *= volPercent;

  ++*currentSample;

  return (int) value;
}

static Pitch GetCurrentInstrumentPitch_Internal (Instrument* instrument, Tempo* tempo, SampleDefinition* sample)
{
  Note* note;
  Pitch targetPitch, *currentPitch;
  int samplesPerTick, *currentSample;
  
  note = GetCurrentInstrumentNote_Internal (instrument);
  currentSample = &instrument->CurrentSampleCount;
  samplesPerTick = GetSamplesPerTick_Internal (tempo, sample);
  currentPitch = &instrument->CurrentPitch;

  targetPitch = (*currentPitch == UnknownNote || !(*currentSample % samplesPerTick))
    ? (note != NULL)
        ? (*currentPitch = note->Tick (note))
        : UnknownNote
    : *currentPitch;
}

static Note* GetCurrentInstrumentNote_Internal (Instrument* instrument)
{
  Note* targetNote, **cNote;
  NoteSource* nSource;

  if (instrument == NULL) return 0;

  cNote = &instrument->CurrentNote;
  nSource = instrument->NoteSource;

  targetNote = (*cNote == NULL || (*cNote)->IsComplete (*cNote))
    ? nSource->NextNote (nSource)
    : *cNote;

  if(*cNote != targetNote)
    *cNote = targetNote;

  return targetNote;
}

static int GetSamplesPerTick_Internal (Tempo* tempo, SampleDefinition* sample)
{
  int samplesPerSecond, ticksPerSecond;

  samplesPerSecond = sample->SamplesPerSecond;
  ticksPerSecond = tempo->TicksPerSecond;

  return samplesPerSecond / ticksPerSecond;
}
