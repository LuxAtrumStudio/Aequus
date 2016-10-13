#ifndef _AEQUUS_FILES_AUDIO_CHUNK_H_
#define _AEQUUS_FILES_AUDIO_CHUNK_H_
#include "../aequus_headers.h"
namespace aequus {
namespace audio {
class Chunk {
public:
  // Load chunk from file
  void Load(std::string file);
  // Sets chunk playback volume
  void Volume(double percent);
  // Terminates chunk and clears memory
  void Terminate();
  // Returns the SDL chunk
  Mix_Chunk *GetChunk();

private:
  // Pointer to SDL chunk data
  Mix_Chunk *chunk = NULL;
};
}
}
#endif // !_AEQUUS_FILES_AUDIO_CHUNK_H_
