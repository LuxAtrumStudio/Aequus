#ifndef AUDIO_CHUNK_CHUNK_HPP
#define AUDIO_CHUNK_CHUNK_HPP
#include "../../sdl_headers.hpp"
#include <string>
namespace aequus {
namespace audio {
class Chunk {
public:
  bool Init(std::string file);
  void SetVolume(int vol);
  void Delete();
  Mix_Chunk *GetChunk();

private:
  std::string filedir;
  Mix_Chunk *mixchunk = NULL;
};
}
}
#endif
