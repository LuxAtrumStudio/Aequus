#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "surface.hpp"
#include <pessum.h>
#include <string>

aequus::video::Object::Surface::Surface(std::string filepath) {
  imagepath = filepath;
  sdlsurface = IMG_Load(imagepath.c_str());
  if (sdlsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to load image file",
                            AVOS, "Surface");
    framework::GetSdlError(framework::IMG);
  } else if (sdlsurface != NULL) {
    sourcerect[0] = sdlsurface->w;
    sourcerect[1] = sdlsurface->h;
    destrect[0] = sdlsurface->w;
    destrect[1] = sdlsurface->h;
    width = sdlsurface->w;
    height = sdlsurface->h;
    x = 0;
    y = 0;
  }
}

aequus::video::Object::Surface::~Surface() { SDL_FreeSurface(sdlsurface); }
