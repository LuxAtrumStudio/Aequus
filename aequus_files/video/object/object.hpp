#ifndef VIDEO_OBJECT_OBJECT_HPP
#define VIDEO_OBJECT_OBJECT_HPP
#include "../../sdl_headers.hpp"
#include "image/image.hpp"
#include "text/text.hpp"
#include <string>
namespace aequus {
namespace video {
enum ObjectType { IMAGE, TEXT };
class Object {
public:
  void InitImg(std::string str, SDL_Renderer *renderer);
  void InitTxt(std::string text, std::string fontname, SDL_Renderer *renderer);
  void Delete();
  void Display();
  SDL_Renderer *sdlrenderer;
  ObjectType objtype;
  Image imageobj;
  Text textobj;
};
}
}
#endif
