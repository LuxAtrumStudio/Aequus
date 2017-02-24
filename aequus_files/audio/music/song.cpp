#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "song.hpp"
#include <pessum.h>
#include <string>

void aequus::audio::music::Song::Init(std::string file) {
  if (mixsong != NULL) {
    Delete();
  }
  mixsong = Mix_LoadMUS(file.c_str());
  if (mixsong == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load music file \"" + file + "\"",
                            logmap["AEQ_AUD_MUS_SON"], "Init");
    framework::GetSdlError(framework::MIX);
  } else {
    for (int i = file.size() - 1; i > 0 && i != '/'; i--) {
      name.insert(name.begin(), file[i]);
    }
    filedir = file;
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "Loaded music file \"" + file + "\"",
                            logmap["AEQ_AUD_MUS_SON"], "Init");
  }
}

void aequus::audio::music::Song::Delete() {
  if (mixsong != NULL) {
    Mix_FreeMusic(mixsong);
    mixsong = NULL;
    filedir = "";
    name = "";
  }
}

std::string aequus::audio::music::Song::GetFile() { return (filedir); }

std::string aequus::audio::music::Song::GetName() { return (name); }

Mix_Music *aequus::audio::music::Song::GetMixSong() { return (mixsong); }
