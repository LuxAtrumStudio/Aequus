#include "../aequus_headers.hpp"
#include "music.hpp"
#include <fstream>
#include <pessum.h>

namespace aequus {
namespace audio {
namespace music {
std::vector<Song> songs;
int currentsong = 0;
int logloc = 0;
bool autoplay = false, shuffle = false, playing = false;
int loops = 1, fadein = 0, fadeout = 0;
double position = 0;
}
}
}

void aequus::audio::music::InitalizeMusic() {
  logloc = pessum::logging::AddLogLocation("aequus_files/audio/music.cpp");
}

void aequus::audio::music::LoadSong(std::string file) {
  Song newsong;
  newsong.mixsong = NULL;
  newsong.mixsong = Mix_LoadMUS(file.c_str());
  if (!newsong.mixsong) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load song file: " + file, logloc,
                            "Loadsong");
    framework::GetError(4);
  }
  std::string songfile = "";
  for (unsigned a = file.size() - 1; a > 0 && a != '/'; a--) {
    songfile = file[a] + songfile;
  }
  newsong.songname = songfile;
  songs.push_back(newsong);
}

void aequus::audio::music::PlaySong(int startfadein, int startloops,
                                    double startposition) {
  if (startfadein != -1) {
    fadein = startfadein;
  }
  if (startloops != -1) {
    loops = startloops;
  }
  if (startposition != -1) {
    position = startposition;
  } else {
    position = 0;
  }
  if (songs.size() >= currentsong && songs[currentsong].mixsong != NULL) {
    if (Mix_FadeInMusicPos(songs[currentsong].mixsong, loops, fadein,
                           position) == -1) {
      pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to play song",
                              logloc, "PlaySong");
      framework::GetError(4);
    } else {
      songs.erase(songs.begin() + currentsong);
    }
  } else {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to play song",
                            logloc, "PlaySong");
  }
}

void aequus::audio::music::SetVolume(double percent) {
  Mix_VolumeMusic(percent * 128);
}

void aequus::audio::music::StopSong() {
  if (Mix_PlayingMusic() == 1) {
    Mix_FadeOutMusic(fadeout);
  }
}

void aequus::audio::music::SetAutoPlay(bool setting) { autoplay = setting; }

void aequus::audio::music::SetShuffle(bool setting) { shuffle = setting; }

void aequus::audio::music::FadeOut(int endfadeout) {
  fadeout = endfadeout;
  Mix_FadeOutMusic(fadeout);
}

void aequus::audio::music::LoadPlaylist(std::string folder) {
  std::vector<std::string> filepaths;
  std::string playlistfile = folder + "/songs.lux";
  filepaths = pessum::luxreader::LoadLuxListFile(playlistfile);
  for (unsigned a = 0; a < filepaths.size(); a++) {
    filepaths[a] = folder + "/" + filepaths[a];
    LoadSong(filepaths[a]);
  }
}

void aequus::audio::music::ClearQueue() { songs.clear(); }

void aequus::audio::music::Update() {
  if (playing == false && Mix_PlayingMusic() == 1) {
    playing = true;
  }
  if (playing == true && Mix_PlayingMusic() != 1) {
    currentsong++;
    if (shuffle == true) {
      currentsong = rand() % songs.size();
    }
    if (autoplay == true) {
      PlaySong();
    } else {
      playing = false;
    }
  }
}

void aequus::audio::music::TerminateMusic() { Mix_CloseAudio(); }
