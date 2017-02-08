#ifndef AUDIO_MUSIC_SONG_HPP
#define AUDIO_MUSIC_SONG_HPP
#include "../../sdl_headers.hpp"
#include <string>
namespace aequus {
namespace audio {
namespace music {
class Song {
public:
  void Init(std::string file);
  void Delete();
  std::string GetFile();
  std::string GetName();
  Mix_Music *GetMixSong();

private:
  std::string filedir = "", name = "";
  Mix_Music *mixsong = NULL;
};
}
}
}
#endif
