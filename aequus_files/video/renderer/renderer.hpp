#ifndef VIDEO_RENDERER_RENDERER_HPP
#define VIDEO_RENDERER_RENDERER_HPP
#include "../../sdl_headers.hpp"
#include <string>
namespace aequus {
namespace video {
enum RendererFlags {
  SOFTWARE = SDL_RENDERER_SOFTWARE,
  ACCELERATED = SDL_RENDERER_ACCELERATED,
  VSYNC = SDL_RENDERER_PRESENTVSYNC,
  TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
};
class Renderer {
public:
  void Init(SDL_Window *sdlwindow, Uint32 flags, std::string name = "");
  void Delete();
  void Display();
  void Clear();
  SDL_Renderer *GetRenderer();

private:
  SDL_Renderer *sdlrenderer = NULL;
  std::string windowname;
};
}
}
#endif
