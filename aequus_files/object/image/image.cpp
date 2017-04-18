#include <pessum.h>
#include <string>
#include "../../aequus_core.hpp"
#include "../object_base.hpp"
#include "image.hpp"

aequus::Image::Image() {}

aequus::Image::Image(SDL_Renderer* renderer) { sdl_renderer = renderer; }

aequus::Image::Image(std::string path) {
  file_path = path;
  if (sdl_surface != NULL) {
    SDL_FreeSurface(sdl_surface);
    sdl_surface = NULL;
  }
  sdl_surface = IMG_Load(file_path.c_str());
  if (sdl_surface == NULL) {
    pessum::Log(pessum::ERROR, "Failed to load image file: %s",
                "aequus/Image/Image", file_path.c_str());
    SdlError(IMG);
  }
}

aequus::Image::Image(std::string path, SDL_Renderer* renderer) {
  sdl_renderer = renderer;
  file_path = path;
  if (sdl_surface != NULL) {
    SDL_FreeSurface(sdl_surface);
    sdl_surface = NULL;
  }
  sdl_surface = IMG_Load(file_path.c_str());
  if (sdl_surface == NULL) {
    pessum::Log(pessum::ERROR, "Failed to load image file: %s",
                "aequus/Image/Image", file_path.c_str());
    SdlError(IMG);
  } else {
    CreateSdlTexture();
  }
}

aequus::Image::~Image() {}

void aequus::Image::SetFile(std::string path) {
  file_path = path;
  if (sdl_surface != NULL) {
    SDL_FreeSurface(sdl_surface);
    sdl_surface = NULL;
  }
  sdl_surface = IMG_Load(file_path.c_str());
  if (sdl_surface == NULL) {
    pessum::Log(pessum::ERROR, "Failed to load image file: %s",
                "aequus/Image/Image", file_path.c_str());
    SdlError(IMG);
  } else {
    CreateSdlTexture();
  }
}

void aequus::Image::SetRenderer(SDL_Renderer* renderer) {
  sdl_renderer = renderer;
  CreateSdlTexture();
}

int aequus::Image::Type() { return (AEQ_OBJ_IMAGE); }
