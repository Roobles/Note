#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#include "instrument.h"
#include "score.h"
#include "musician.h"
#include "sampledefinition.h"

// Declarations
WavFile* BuildTestFile (MusicSequence* music, SampleDefinition* sample);
Instrument* BuildTestInstrument ();
NoteSequence* BuildTestNoteSequence ();
Score* BuildTestScore ();
Tempo* BuildTestTempo ();
Musician* BuildTestMusician ();
SampleDefinition* BuildTestSampleDefinition ();
void AddTestNotes (NoteSequence* sequence);

// Main
int main (int argc, char** argv)
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
  musician = BuildTestMusician ();

  music = musician->Play (musician, score, sample);
  file = BuildTestFile (music, sample);
  stream = file->ToWavStream (file);
  file->WriteToFile (file, stream, location);

  // Print Frequency
  frequency = music->GetFrequency (music, 0, sample->SamplesPerSecond, 1);
  printf ("Frequency: %d\n", (int)frequency);

  // Print Debug
  //music->PrintDebug (music);

  DestroyScore (score);
  DestroyWavFile (file);
  DestroyMusician (musician);
  DestroyWavStream (stream);

  return 0;
}

Instrument* BuildTestInstrument ()
{
  Instrument* instrument;
  instrument = BuildInstrument ();

  return instrument;
}

Musician* BuildTestMusician ()
{
  Instrument* instrument;
  Musician* musician;

  instrument = BuildTestInstrument ();
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

  AddTestNotes(sequence);

  return sequence;
}

#define AddTestNote(notesv, duration) \
  sequence->AddNote(sequence, BuildNote(notesv, duration))
void AddTestNotes (NoteSequence* sequence)
{
  AddTestNote(D, QuarterNote);
  AddTestNote(C, QuarterNote);
  AddTestNote(B, HalfNote);

  AddTestNote(D, QuarterNote);
  AddTestNote(C, QuarterNote);
  AddTestNote(B, HalfNote);

  AddTestNote(B, EigthNote);
  AddTestNote(B, EigthNote+10);
  AddTestNote(B, EigthNote);
  AddTestNote(B, EigthNote+10);

  AddTestNote(C, EigthNote);
  AddTestNote(C, EigthNote+10);
  AddTestNote(C, EigthNote);
  AddTestNote(C, EigthNote+10);

  AddTestNote(D, QuarterNote);
  AddTestNote(C, QuarterNote);
  AddTestNote(B, HalfNote);
}

SampleDefinition* BuildTestSampleDefinition ()
{
  int sampleRate, sampleSize;
  SampleDefinition* sample;

  sampleRate = 8000;
  sampleSize = 16;
  sample = BuildSampleDefinition (sampleRate, sampleSize); 
}
