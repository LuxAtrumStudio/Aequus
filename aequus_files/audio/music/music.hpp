#ifndef AUDIO_MUSIC_MUSIC_HPP
#define AUDIO_MUSIC_MUSIC_HPP
#include "song.hpp"
namespace aequus {
namespace audio {
namespace music {
void SetVolume(int vol);
void PlayMusic(Song song, int loops = 1);
void StopMusic();
void FadeIn(Song song, int fadein = 0, double position = 0, int loops = 1);
void FadeOut(int fadeout);
void Pause();
void Resume();
void SetPos(double position);
}
}
}
#endif
