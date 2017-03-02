#include "../log_indices.hpp"
#include "../sdl_headers.hpp"
#include "audio.hpp"
#include "audio_headers.hpp"
#include <pessum.h>
#include <string>

namespace aequus {
namespace audio {
int channelcount = -1;
}
}

void aequus::audio::InitDevice(int channels) {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
  InitChannels(channels);
  pessum::logging::Log("SUCCESS", "Initialized audio device", "aeq/aud",
                       "InitDevice");
}

void aequus::audio::DeleteDevice() {
  if (channelcount != -1) {
    Mix_CloseAudio();
  }
  pessum::logging::Log("SUCCESS", "Closed audio device", "aeq/aud",
                       "DeleteDevice");
}

void aequus::audio::InitChannels(int count) {
  Mix_AllocateChannels(count);
  channelcount = count;
}

void aequus::audio::SetChannelVolume(int vol, int channel) {
  if (CheckChannel(channel)) {
    Mix_Volume(channel, vol);
  }
}

void aequus::audio::StopChannel(int channel) {
  if (CheckChannel(channel)) {
    Mix_HaltChannel(channel);
  }
}

void aequus::audio::PlayChunk(std::string file, int channel) {
  Chunk sound;
  if (CheckChannel(channel) && sound.Init(file)) {
    Mix_FadeInChannelTimed(channel, sound.GetChunk(), 1, 0, -1);
  }
}

bool aequus::audio::CheckChannel(int channel) {
  if (channel < 1 || channel > channelcount) {
    pessum::logging::Log("ERROR",
                         "Invalid mixing channel: " + std::to_string(channel),
                         "aeq/aud", "CheckChannel");
    return (false);
  }
  return (true);
}
