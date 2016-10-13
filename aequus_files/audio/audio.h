#ifndef _AEQUUS_FILES_AUDIO_AUDIO_H_
#define _AEQUUS_FILES_AUDIO_AUDIO_H_
#include "../aequus_headers.h"
#include "chunk.h"
namespace aequus {
namespace audio {
class Chunk;
// Stores the number of channels, the currently bound channel, and the currently
// bound chunk
extern int channels, boundchannel, boundchunk;
// Stoes all the loaded audio chunks
extern std::vector<Chunk> chunks;
// Stores the log location pointer
extern int logloc;
// Initalizes the audio system
void InitializeAudio();
// Initalizes the SDL audio device for playback
void InitalizeDevice();
// Terminates the SDL audio device removing it
void TerminateDevice();
// Sets the number of avaliable playback channels for audo playback
void AllocateChannels(int channelcount);
// Binds the current channel for audio playback
void BindChannel(int channel);
// Sets the volume of a channel
void ChannelVolume(double percent = 1, int channel = boundchannel);
// Plays a previously loaded chunck.
// loop number of loops that will be played
// fadein ms of fade in from begining
// time seconds into the audio to begin at
void PlayChunk(int loops = 0, int fadein = 0, int time = -1,
               int chunk = boundchunk, int channel = boundchannel);
// Stops playing any audio on given channel
void StopChannel(int channel = boundchannel);
// Loads and plays sound file on selected channel
void PlaySound(std::string file, int channel = boundchannel);
// Loads sound file to a chunk
void LoadSound(std::string file);
}
}
#endif // !_AEQUUS_FILES_AUDIO_AUDIO_H_
