#ifndef _AEQUUS_FILES_AUDIO_AUDIO_H_
#define _AEQUUS_FILES_AUDIO_AUDIO_H_
#include "../aequus_headers.h"
#include "chunk.h"
namespace aequus {
namespace audio {
class Chunk;
extern int channels, boundchannel, boundchunk;
extern std::vector<Chunk> chunks;
extern int logloc;
void InitializeAudio();
void InitalizeDevice();
void TerminateDevice();
void AllocateChannels(int channelcount);
void BindChannel(int channel);
void ChannelVolume(double percent = 1, int channel = boundchannel);
void PlayChunk(int loops = 0, int fadein = 0, int time = -1,
               int chunk = boundchunk, int channel = boundchannel);
void StopChannel(int channel = boundchannel);
void PlaySound(std::string file, int channel = boundchannel);
void LoadSound(std::string file);
}
}
#endif // !_AEQUUS_FILES_AUDIO_AUDIO_H_
