#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../texture/texture.hpp"
#include "image.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Image::Init(std::string img, SDL_Renderer *renderer) {
  filepath = img;
  SDL_Surface *imgsurface = IMG_Load(filepath.c_str());
  if (imgsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load image file: " + filepath, AVOI,
                            "Init");
    framework::GetSdlError(framework::IMG);
  } else {
    InitTexture(imgsurface, renderer);
  }
}

void aequus::video::Image::UpdateFile(std::string img) {
  filepath = img;
  SDL_Surface *imgsurface = IMG_Load(filepath.c_str());
  if (imgsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load image file: " + filepath, AVOI,
                            "Init");
    framework::GetSdlError(framework::IMG);
  } else {
    InitTexture(imgsurface, NULL);
  }
}

void aequus::video::Image::Delete() {
  DeleteTexture();
  filepath = "";
}
