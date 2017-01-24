#ifndef _AEQUUS_FILES_VIDEO_RENDERER_H_
#define _AEQUUS_FILES_VIDEO_RENDERER_H_
#include "../sdl_headers.hpp"
#include "object/object.hpp"
#include <vector>
namespace aequus {
namespace video {
// Renderer class, used to store all data for an SDL renderer, aswell as
// running all basic renderer funcitons, such as changing settings
// and basic draw functions.
class Renderer {
public:
  // Used to set renderer mode between the different poslible SDL modes
  enum RendererFlags {
    SOFTWARE = SDL_RENDERER_SOFTWARE,
    ACCELERATED = SDL_RENDERER_ACCELERATED,
    VSYNC = SDL_RENDERER_PRESENTVSYNC,
    TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
  };
  // Sets the blending mode for the renderer
  enum BlendMode {
    NONE = SDL_BLENDMODE_NONE,
    BLEND = SDL_BLENDMODE_BLEND,
    ADD = SDL_BLENDMODE_ADD,
    MOD = SDL_BLENDMODE_MOD
  };
  // The pointer to the SDL renderer
  SDL_Renderer *sdlrenderer;
  // Internal storage of the renderer mode, for functions to check against
  Uint32 rendererflag;
  // Genoreates a new renderer from a given window, and creates the log
  void CreateRenderer(SDL_Window *sdlwindow, std::string title,
                      Uint32 flags = TARGETTEXTURE);
  // Destroys the renderer, but not the window
  void DestroyRenderer();
  // Sets a texture to render to
  void SetTargetTexture(Object target);
  // Sets the viewport of the renderer
  // x, y, width, height
  void SetViewport(int rect[4] = 0);
  // Sets the scale in an x factor and y factor of the renderer
  void SetScale(float scalex, float scaley);
  // Sets the resolution of the renderer, without changing the window
  void SetResolution(int width, int height);
  // Sets the zone to renderer to on the target texture
  // x, y, width, height
  void SetTargetClip(int rect[4] = 0);
  // Updates the renderer and displays everything that has been drawn
  void Update();
  // Clears the renderer with the current draw color
  void Clear();
  // Sets the background color of the renderer/window
  void SetColor(double red = 0, double green = 0, double blue = 0,
                double alpha = 1);

private:
  // Sets log location for aequus framework logging
  int logloc = 0;
  // Storage for background color of renderer/window
  double color[4] = {0, 0, 0, 1};
};
}
}
#endif // !_AEQUUS_FILES_VIDEO_RENDERER_H_
