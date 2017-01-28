#ifndef AEQUUS_VIDEO_IMAGE_IMAGE_HPP
#define AEQUUS_VIDEO_IMAGE_IMAGE_HPP
#include "../../../sdl_headers.hpp"
#include "../../video_enums.hpp"
#include "../texture/texture.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Image : public Texture {
public:
  void Init(std::string img, SDL_Renderer *renderer);
  void UpdateFile(std::string img = "");
  void Delete();

private:
  std::string filepath = "";
};
}
}
#endif
