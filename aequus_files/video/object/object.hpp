#ifndef VIDEO_OBJECT_OBJECT_HPP
#define VIDEO_OBJECT_OBJECT_HPP
#include "../../sdl_headers.hpp"
#include "texture/texture.hpp"
#include <string>
namespace aequus {
namespace video {
enum ObjectType { TEXTURE };
class Object {
public:
  void Init(std::string str, SDL_Renderer *renderer);
  void Delete();
  void Display();

private:
  SDL_Renderer *sdlrenderer;
  ObjectType objtype;
  Texture objtexture;
};
}
}
#endif
