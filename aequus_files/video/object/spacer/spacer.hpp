#ifndef VIDEO_OBJECT_SPACER_SPACER_HPP
#define VIDEO_OBJECT_SPACER_SPACER_HPP
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Spacer : public Object {
public:
  void Init(int w, int h);
  void Delete();

private:
  int width, height;
};
}
}
#endif
