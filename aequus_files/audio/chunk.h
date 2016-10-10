#ifndef _AEQUUS_FILES_AUDIO_CHUNK_H_
#define _AEQUUS_FILES_AUDIO_CHUNK_H_
#include "../aequus_headers.h"
namespace aequus {
namespace audio {
class Chunk {
 public:
  void Load(std::string file);
  void Volume(double percent);
  void Terminate();
  Mix_Chunk* GetChunk();

 private:
  Mix_Chunk* chunk = NULL;
};
}
}
#endif  // !_AEQUUS_FILES_AUDIO_CHUNK_H_
