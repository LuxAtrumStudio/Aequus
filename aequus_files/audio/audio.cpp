#include "audio.h"
#include <pessum.h>
#include "../aequus_headers.h"

namespace aequus {
namespace audio {
int channels = 0, boundchannel = 0, boundchunk = 0;
std::vector<Chunk> chunks;
int logloc = 0;
}
}

void aequus::audio::InitializeAudio() {
  logloc = pessum::logging::AddLogLocation("aequus_files/audio/audio.cpp");
  InitalizeDevice();
  music::InitalizeMusic();
}

void aequus::audio::InitalizeDevice() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
  AllocateChannels(1);
  channels = 1;
}

void aequus::audio::TerminateDevice() { Mix_CloseAudio(); }

void aequus::audio::AllocateChannels(int channelcount) {
  Mix_AllocateChannels(channelcount);
  channels = channelcount;
}

void aequus::audio::BindChannel(int channel) {
  if (channel <= channels) {
    boundchannel = channel;
  }
}

void aequus::audio::ChannelVolume(double percent, int channel) {
  Mix_Volume(channel, percent * 128);
}

void aequus::audio::PlayChunk(int loops, int fadein, int time, int chunk,
                              int channel) {
  Mix_FadeInChannelTimed(channel, chunks[chunk].GetChunk(), loops, fadein,
                         time);
}

void aequus::audio::StopChannel(int channel) { Mix_HaltChannel(channel); }

void aequus::audio::PlaySound(std::string file, int channel) {
  LoadSound(file);
  PlayChunk();
}

void aequus::audio::LoadSound(std::string file) {
  Chunk newchunk;
  newchunk.Load(file);
  chunks.push_back(newchunk);
  boundchunk = chunks.size() - 1;
}
