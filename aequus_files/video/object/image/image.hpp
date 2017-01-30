#ifndef VIDEO_OBJECT_IMAGE_IMAGE_HPP
#define VIDEO_OBJECT_IMAGE_IMAGE_HPP
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Image : public Object {
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
