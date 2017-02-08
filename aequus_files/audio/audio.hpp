#ifndef AUDIO_AUDIO_HPP
#define AUDIO_AUDIO_HPP
#include <string>
namespace aequus {
namespace audio {
extern int channelcount;
void InitDevice(int channels = 1);
void DeleteDevice();
void InitChannels(int count = 1);
void SetChannelVolume(int vol, int channel);
void StopChannel(int channel);
void PlayChunk(std::string file, int channel);
bool CheckChannel(int channel);
}
}
#endif
