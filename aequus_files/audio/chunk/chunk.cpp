#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "chunk.hpp"
#include <pessum.h>
#include <string>

bool aequus::audio::Chunk::Init(std::string file) {
  filedir = file;
  mixchunk = Mix_LoadWAV(file.c_str());
  if (mixchunk == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load chunk \"" + file + "\"",
                            logmap["AEQ_AUD_CHU"], "Init");
    framework::GetSdlError(framework::MIX);
    return (false);
  }
  pessum::logging::LogLoc(pessum::logging::SUCCESS,
                          "Loaded chunk \"" + file + "\"",
                          logmap["AEQ_AUD_CHU"], "Init");
  return (true);
}

void aequus::audio::Chunk::SetVolume(int vol) {
  if (mixchunk != NULL) {
    Mix_VolumeChunk(mixchunk, vol);
  }
}

void aequus::audio::Chunk::Delete() {
  if (mixchunk != NULL) {
    Mix_FreeChunk(mixchunk);
    mixchunk = NULL;
  }
}

Mix_Chunk *aequus::audio::Chunk::GetChunk() { return (mixchunk); }
