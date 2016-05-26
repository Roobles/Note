#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

// Declarations
WavFile* BuildTestFile();
NoteSequence* BuildTestNoteSequence();
Score* BuildTestScore();
void AddTestNotes(NoteSequence* sequence);

// Main
int main (int argc, char** argv)
{
  WavFile* testFile;
  Score* score;

  testFile = BuildTestFile ();
  score = testFile->Score;

  PrintScore (score);
  

  DestroyWavFile (testFile);

  return 0;
}

// Functions
WavFile* BuildTestFile()
{
  char* wavName = "TestName";
  NoteSequence* sequence;
  Score* score;
  WavFile* testFile;

  score = BuildTestScore();
  testFile = BuildWavFile(wavName, score);

  return testFile;
}

Score* BuildTestScore()
{
  Score* score;
  NoteSequence* sequence;

  sequence = BuildTestNoteSequence();
  score = BuildScore(Standard, sequence);

  return score;
}

NoteSequence* BuildTestNoteSequence()
{
  NoteSequence* sequence;
  sequence = BuildNoteSequence();

  AddTestNotes(sequence);

  return sequence;
}

#define AddTestNote(notesv, duration) \
  sequence->AddNote(sequence, BuildNote(notesv, duration))
void AddTestNotes(NoteSequence* sequence)
{
  AddTestNote(A, 4);
  AddTestNote(C, 2);
}
