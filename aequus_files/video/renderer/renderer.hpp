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
enum BlendMode {
  NONE = SDL_BLENDMODE_NONE,
  BLEND = SDL_BLENDMODE_BLEND,
  ADD = SDL_BLENDMODE_ADD,
  MOD = SDL_BLENDMODE_MOD
};
class Renderer {
public:
  Renderer(SDL_Window *sdlwindow, Uint32 flags, std::string name = "");
  Renderer();
  ~Renderer();
  void Display();

private:
  SDL_Renderer *sdlrenderer = NULL;
  std::string windowname;
};
}
}
#endif
