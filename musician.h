#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "score.h"
#include "instrument.h"
#include "musicsequence.h"

typedef struct Musician Musician;

struct Musician
{
  Instrument* Instrument;
  MusicSequence* (*Play) (Musician* musician, Score* score, SampleDefinition* sample);
};

Musician* BuildMusician (Instrument* instrument);
void DestroyMusician (Musician* musician);

#endif
