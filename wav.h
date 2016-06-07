#ifndef WAV_H
#define WAV_H

#include "musicsequence.h"
#include "sampledefinition.h"

#define MAX_WAV_FILE_NAME 255

typedef struct WavStream WavStream;
struct WavStream
{
  int Length;
  char* Stream;
};

typedef struct WavFile WavFile;
struct WavFile
{
  // Metadata
  char Name[MAX_WAV_FILE_NAME];
  MusicSequence* Music;

  // Wav Specification
  char RiffId[4];
  int WavChunkSize;
  char WavId[4];
  char FormatId[4];
  int FormatChunkSize;
  short FormatTag;
  short NumberOfChannels;
  int SamplesPerSecond;
  int AverageBytesPerSecond;
  short BlockAlign;
  short BitsPerSample;
  char DataId[4];
  int DataSize;
  char* Data; 
  char Padding;

  WavStream* (*ToWavStream) (WavFile* file);
  void (*WriteToFile) (WavFile* file, WavStream* stream, const char* location);
};

WavFile* BuildWavFile (char* name, MusicSequence* music, SampleDefinition* sample);
void DestroyWavFile (WavFile* file);

WavStream* BuildWavStream (int length);
void DestroyWavStream (WavStream* stream);

#endif
