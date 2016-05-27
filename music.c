#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#include "instrument.h"
#include "score.h"

// Declarations
WavFile* BuildTestFile ();
Instrument* BuildTestInstrument ();
NoteSequence* BuildTestNoteSequence ();
Score* BuildTestScore ();
Tempo* BuildTestTempo ();
void AddTestNotes (NoteSequence* sequence);

// Main
int main (int argc, char** argv)
{
  Instrument* instrument;
  Score* score;

  instrument = BuildInstrument();
  score = BuildTestScore();

  instrument->SetNoteSource(instrument, (NoteSource*) score->Notes);

  instrument->PlayTick(instrument);

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
