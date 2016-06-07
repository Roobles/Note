#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

// Static Function Declarations
static WavStream* ToWavStream_Internal (WavFile* file);
static void PackData (WavFile* file, MusicSequence* music, SampleDefinition* sample);
static void WriteToFile_Internal (WavFile* file, WavStream* stream, const char* location);
static void WriteString (char** stream, char* value, int len);
static void WriteInteger (char** stream, int value);
static void WriteShort (char** stream, short value);

// wav.h Implementation
WavFile* BuildWavFile(char* name, MusicSequence* music, SampleDefinition* sample)
{
  WavFile* file;
  int samplesPerSecond, bitDepth, byteDepth, 
    padding, samples, totalSampleSize;

  samplesPerSecond = sample->SamplesPerSecond;
  bitDepth = sample->BitsPerSample;
  samples = music->Length;

  file = malloc (sizeof (WavFile));
  strncpy (file->Name, name, MAX_WAV_FILE_NAME);
  file->Music = music;
  
  byteDepth = bitDepth / 8;
  totalSampleSize = byteDepth * samples;
  padding = totalSampleSize % 2;

  strcpy (file->RiffId, "RIFF");
  strcpy (file->WavId, "WAVE");
  strcpy (file->FormatId, "fmt ");
  strcpy (file->DataId, "data");

  file->WavChunkSize = 36 + totalSampleSize + padding;
  file->FormatChunkSize = 16;
  file->FormatTag = 1;
  file->NumberOfChannels = 1;
  file->SamplesPerSecond = samplesPerSecond;
  file->AverageBytesPerSecond = samplesPerSecond * byteDepth;
  file->BlockAlign = byteDepth;
  file->BitsPerSample = bitDepth;
  file->DataSize = totalSampleSize;
  file->Padding = padding;

  PackData (file, music, sample);

  file->ToWavStream = ToWavStream_Internal;
  file->WriteToFile = WriteToFile_Internal;

  return file;
}

void DestroyWavFile(WavFile* file)
{
  strcpy (file->Name, "");
  DestroyMusicSequence (file->Music);

  file->ToWavStream = NULL;
  file->WriteToFile = NULL;

  free (file->Data);
  free (file);
}

WavStream* BuildWavStream (int length)
{
  WavStream* stream;

  stream = malloc (sizeof (WavStream));
  if (length < 1) return stream;

  stream->Length = length;
  stream->Stream = malloc (length);

  return stream;
}

void DestroyWavStream (WavStream* stream)
{
  if (stream == NULL) return;
  
  if (stream->Length > 0)
    free (stream->Stream);

  stream->Length = 0x0;
  free (stream);
}

// Static Function Implementations
static WavStream* ToWavStream_Internal (WavFile* file)
{
  int absoluteSize;
  char* byteStream, *ittr;
  WavStream* wavStream;

  absoluteSize = 8 + file->WavChunkSize;
  wavStream = BuildWavStream (absoluteSize);
  byteStream = wavStream->Stream;

  WriteString   (&byteStream, file->RiffId, 4);
  WriteInteger  (&byteStream, file->WavChunkSize);
  WriteString   (&byteStream, file->WavId, 4);
  WriteString   (&byteStream, file->FormatId, 4);
  WriteInteger  (&byteStream, file->FormatChunkSize);
  WriteShort    (&byteStream, file->FormatTag);
  WriteShort    (&byteStream, file->NumberOfChannels);
  WriteInteger  (&byteStream, file->SamplesPerSecond);
  WriteInteger  (&byteStream, file->AverageBytesPerSecond);
  WriteShort    (&byteStream, file->BlockAlign);
  WriteShort    (&byteStream, file->BitsPerSample);
  WriteString   (&byteStream, file->DataId, 4);
  WriteInteger  (&byteStream, file->DataSize);

  memcpy (byteStream, file->Data, file->DataSize);

  return wavStream;
}

static void WriteToFile_Internal (WavFile* file, WavStream* stream, const char* location)
{
  int tfLen, locLen, nameLen;
  char* targetFileStr;
  char* fileMode;
  FILE *targetFilePtr;

  int streamLength, streamValueSize, written;
  char* streamData;

  fileMode = "w";
  locLen = strlen (location);
  nameLen = strlen (file->Name);
  tfLen = locLen + nameLen + 1;
  targetFileStr = malloc (tfLen);

  sprintf (targetFileStr, "%s%s", location, file->Name);
  targetFilePtr = fopen (targetFileStr, fileMode);

  streamValueSize = sizeof (char);
  streamLength = stream->Length;
  streamData = stream->Stream;
  written = fwrite (streamData, streamValueSize, streamLength, targetFilePtr);

  free (targetFileStr);
}

#define GetByteValue(mtval, mtbyteCount) (unsigned char) ((mtval >> (8 * mtbyteCount)) & 0xFF)
#define SetByteValue(mtstream, mtval, mtbyteCount) **mtstream = GetByteValue(mtval, mtbyteCount); ++*mtstream
static void PackData (WavFile* file, MusicSequence* music, SampleDefinition* sample)
{
  int musicIttr, dataIttr, i, dataSize, musicLength, byteDepth;
  int musicVal;
  char* data;

  byteDepth = sample->BitsPerSample / 8;
  dataSize = file->DataSize;
  musicLength = music->Length;
  
  data = file->Data = malloc (dataSize);
  for (musicIttr=0; musicIttr < musicLength; musicIttr++)
  {
    musicVal = music->Samples[musicIttr];
    for (i = 0; i < byteDepth; i++)
    {
      dataIttr = musicIttr * byteDepth + i;
      data[dataIttr] = (musicVal >> i*8) & 0xFF;
    }
  }
}

static void WriteString (char** stream, char* value, int len)
{
  strncpy (*stream, value, len);
  *stream += len;
}

static void WriteInteger (char** stream, int value)
{
  SetByteValue (stream, value, 0);
  SetByteValue (stream, value, 1);
  SetByteValue (stream, value, 2);
  SetByteValue (stream, value, 3);
}

static void WriteShort (char** stream, short value)
{
  SetByteValue (stream, value, 0);
  SetByteValue (stream, value, 1);
}
