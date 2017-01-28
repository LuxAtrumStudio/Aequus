#ifndef VIDEO_OBJECT_OBJECT_HPP
#define VIDEO_OBJECT_OBJECT_HPP
#include "../../sdl_headers.hpp"
#include "image/image.hpp"
#include <string>
namespace aequus {
namespace video {
enum ObjectType { IMAGE };
class Object {
public:
  void Init(std::string str, SDL_Renderer *renderer);
  void Delete();
  void Display();
  SDL_Renderer *sdlrenderer;
  ObjectType objtype;
  Image imageobj;
};
}
}
#endif
