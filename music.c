#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#include "instrument.h"
#include "score.h"
#include "sampledefinition.h"

// Declarations
WavFile* BuildTestFile ();
Instrument* BuildTestInstrument ();
NoteSequence* BuildTestNoteSequence ();
Score* BuildTestScore ();
Tempo* BuildTestTempo ();
SampleDefinition* BuildTestSampleDefinition ();
void AddTestNotes (NoteSequence* sequence);

// Main
int main (int argc, char** argv)
{
  Score* score;
  Tempo* tempo;
  Instrument* instrument;
  SampleDefinition* sample;
  int sampleVal, i;

  instrument = BuildInstrument ();
  score = BuildTestScore ();
  sample = BuildTestSampleDefinition ();
  tempo = score->Tempo;

  instrument->SetNoteSource(instrument, (NoteSource*) score->Notes);
  i = 1;
  for (sampleVal = -1; sampleVal; sampleVal = instrument->PlaySample(instrument, tempo, sample))
    if (sampleVal > 0) printf ("Sample (%05d): %d\n", i++, sampleVal);

  PrintScore (score);
  DestroyScore (score);
  DestroyInstrument (instrument);

  return 0;
}

Instrument* BuildTestInstrument ()
{
  Instrument* instrument;
  instrument = BuildInstrument ();

  return instrument;
}

// Functions
WavFile* BuildTestFile ()
{
  char* wavName = "TestName";
  NoteSequence* sequence;
  Score* score;
  WavFile* testFile;

  score = BuildTestScore ();
  testFile = BuildWavFile (wavName, score);

  return testFile;
}

Score* BuildTestScore ()
{
  Score* score;
  Tempo* tempo;
  NoteSequence* sequence;

  tempo = BuildTestTempo ();
  sequence = BuildTestNoteSequence();
  score = BuildScore(tempo, sequence);

  return score;
}

Tempo* BuildTestTempo ()
{
  Tempo* tempo;

  tempo = BuildTempo(120, QuarterNote);
  return tempo;
}

NoteSequence* BuildTestNoteSequence ()
{
  NoteSequence* sequence;
  sequence = BuildNoteSequence();

  AddTestNotes(sequence);

  return sequence;
}

#define AddTestNote(notesv, duration) \
  sequence->AddNote(sequence, BuildNote(notesv, duration))
void AddTestNotes (NoteSequence* sequence)
{
  AddTestNote(A, QuarterNote);
  AddTestNote(C, WholeNote);
}

SampleDefinition* BuildTestSampleDefinition ()
{
  int sampleRate, sampleSize;
  SampleDefinition* sample;

  sampleRate = 8000;
  sampleSize = 16;
  sample = BuildSampleDefinition (sampleRate, sampleSize); 
}
