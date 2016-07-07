#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#include "instrument.h"
#include "score.h"
#include "musician.h"
#include "sampledefinition.h"
#include "periodgenerator.h"

// Declarations
WavFile* BuildTestFile (MusicSequence* music, SampleDefinition* sample);
Instrument* BuildTestInstrument (SampleDefinition* definition);
NoteSequence* BuildTestNoteSequence ();
Score* BuildTestScore ();
Tempo* BuildTestTempo ();
Musician* BuildTestMusician (SampleDefinition* definition);
SampleDefinition* BuildTestSampleDefinition ();
void AddTestNotes (NoteSequence* sequence);
void AddTestRange (NoteSequence* sequence);
void Exploratory ();
void HotCrossBuns ();

// Main
int main (int argc, char** argv)
{
  HotCrossBuns ();
  //Exploratory ();
  return 0;
}

void HotCrossBuns ()
{
  Score* score;
  Tempo* tempo;
  Musician* musician;
  MusicSequence* music;
  SampleDefinition* sample;
  WavFile* file;
  WavStream* stream;
  int sampleVal, i;
  char* location = "./";
  double frequency;

  score = BuildTestScore ();
  sample = BuildTestSampleDefinition ();
  tempo = score->Tempo;
  musician = BuildTestMusician (sample);

  music = musician->Play (musician, score);
  file = BuildTestFile (music, sample);
  stream = file->ToWavStream (file);
  file->WriteToFile (file, stream, location);

  DestroyScore (score);
  DestroyWavFile (file);
  DestroyMusician (musician);
  DestroyWavStream (stream);
}

Instrument* BuildTestInstrument (SampleDefinition* definition)
{
  Instrument* instrument;
  instrument = BuildInstrument (definition);

  return instrument;
}

Musician* BuildTestMusician (SampleDefinition* definition)
{
  Instrument* instrument;
  Musician* musician;

  instrument = BuildTestInstrument (definition);
  musician = BuildMusician (instrument);

  return musician;
}

// Functions
WavFile* BuildTestFile (MusicSequence* music, SampleDefinition* sample)
{
  char* wavName = "TestName";
  WavFile* testFile;
  testFile = BuildWavFile (wavName, music, sample);

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

  //AddTestRange (sequence);
  AddTestNotes(sequence);

  return sequence;
}

#define AddTestNote(notesv, duration) \
  sequence->AddNote(sequence, BuildNote(notesv, duration))
void AddTestNotes (NoteSequence* sequence)
{
  AddTestNote (D, QuarterNote);
  AddTestNote (C, QuarterNote);
  AddTestNote (B, HalfNote);

  AddTestNote (D, QuarterNote);
  AddTestNote (C, QuarterNote);
  AddTestNote (B, HalfNote);

  AddTestNote (B, EigthNote);
  AddTestNote (B, EigthNote);
  AddTestNote (B, EigthNote);
  AddTestNote (B, EigthNote);

  AddTestNote (C, EigthNote);
  AddTestNote (C, EigthNote);
  AddTestNote (C, EigthNote);
  AddTestNote (C, EigthNote);

  AddTestNote (D, QuarterNote);
  AddTestNote (C, QuarterNote);
  AddTestNote (B, HalfNote);
}

void AddTestRange (NoteSequence* sequence)
{
  int i, freqCount;
  int startFrequency, endFrequency, 
    frequencyGap, duration;

  startFrequency = 40;
  endFrequency = 2000;
  frequencyGap = 10;
  duration = EigthNote;

  for (i=startFrequency; i<endFrequency; i+=frequencyGap)
    AddTestNote (i, duration);
}

SampleDefinition* BuildTestSampleDefinition ()
{
  int sampleRate, sampleSize;
  SampleDefinition* sample;

  sampleRate = 8000;
  sampleSize = 16;
  sample = BuildSampleDefinition (sampleRate, sampleSize); 
}

void Exploratory ()
{
  Score* score;
  Instrument* instrument;
  SampleDefinition* definition;
  MusicSequence* music;

  score = BuildTestScore ();
  definition = BuildTestSampleDefinition ();
  instrument = BuildTestInstrument (definition);

  instrument->SetNoteSource (instrument, (NoteSource*) score->Notes);
  music = instrument->PlayNote (instrument, score->Tempo);
}
