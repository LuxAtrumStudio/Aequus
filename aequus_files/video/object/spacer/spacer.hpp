#ifndef VIDEO_OBJECT_IMAGE_IMAGE_HPP
#define VIDEO_OBJECT_IMAGE_IMAGE_HPP
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Spacer : public Object {
public:
  void Init(int w, int h, bool resize);
  void Resize(int w, int h);
  void Delete();

private:
  int width, height;
  bool resizeable = false;
};
}
}
#endif
