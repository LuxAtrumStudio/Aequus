#include "chunk.h"

void aequus::audio::Chunk::Load(std::string file) {
  chunk = Mix_LoadWAV(file.c_str());
}

void aequus::audio::Chunk::Volume(double percent) {
  Mix_VolumeChunk(chunk, percent * 128);
}

void aequus::audio::Chunk::Terminate() { Mix_FreeChunk(chunk); }

Mix_Chunk* aequus::audio::Chunk::GetChunk() {
  if (chunk == NULL) {
    return (NULL);
  } else {
    return (chunk);
  }
}
