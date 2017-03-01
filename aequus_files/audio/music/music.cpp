#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "music.hpp"
#include "song.hpp"
#include <pessum.h>
#include <string>

namespace aequus {
namespace audio {
namespace music {
std::vector<Song> queue;
}
}
}

void aequus::audio::music::SetVolume(int vol) { Mix_VolumeMusic(vol); }

void aequus::audio::music::PlayMusic(Song song, int loops) {
  if (Mix_PlayMusic(song.GetMixSong(), loops) == -1) {
    pessum::logging::Log("ERROR",
                         "Failed to playsong: \"" + song.GetFile() + "\"",
                         "aeq/aud/mus", "PlayMusic");
    framework::GetSdlError(framework::MIX);
  }
}

void aequus::audio::music::StopMusic() { Mix_HaltMusic(); }

void aequus::audio::music::FadeIn(Song song, int fadein, double position,
                                  int loops) {
  if (Mix_FadeInMusicPos(song.GetMixSong(), loops, fadein, position) == -1) {
    pessum::logging::Log("ERROR",
                         "Failed to playsong: \"" + song.GetFile() + "\"",
                         "aeq/aud/mus", "FadeIn");
    framework::GetSdlError(framework::MIX);
  }
}

void aequus::audio::music::FadeOut(int fadeout) {
  if (Mix_PlayingMusic() == 1) {
    Mix_FadeOutMusic(fadeout);
  }
}

void aequus::audio::music::Pause() {
  if (Mix_PausedMusic() == 0) {
    Mix_PauseMusic();
  }
}

void aequus::audio::music::Resume() {
  if (Mix_PausedMusic() == 1) {
    Mix_ResumeMusic();
  }
}

void aequus::audio::music::SetPos(double position) {
  if (Mix_PlayingMusic() == 1) {
    Mix_RewindMusic();
    Mix_SetMusicPosition(position);
  }
}

void aequus::audio::music::AddSongToQueue(Song song) { queue.push_back(song); }

void aequus::audio::music::AutoPlayQueue() {
  if (queue.size() > 1 && Mix_PlayingMusic() == 0) {
    queue.erase(queue.begin());
    PlayMusic(queue[0]);
  }
}
