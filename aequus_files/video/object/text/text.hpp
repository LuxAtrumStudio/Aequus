#ifndef VIDEO_OBJECT_TEXT_TEXT_HPP
#define VIDEO_OBJECT_TEXT_TEXT_HPP
#include "../../../sdl_headers.hpp"
#include "../../video_enums.hpp"
#include "../texture/texture.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Text : public Texture {
public:
  void Init();
  void UpdateString(std::string newstr = "");
  void Delete();

private:
};
}
}
#endif
