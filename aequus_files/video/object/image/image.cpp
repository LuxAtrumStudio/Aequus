#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "image.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Image::Init(std::string img, SDL_Renderer *renderer) {
  filepath = img;
  SDL_Surface *imgsurface = IMG_Load(filepath.c_str());
  if (imgsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load image file: " + filepath,
                            LOG_AEQ_VID_OBJ_IMG, "Init");
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
                            "Failed to load image file: " + filepath,
                            LOG_AEQ_VID_OBJ_IMG, "Init");
    framework::GetSdlError(framework::IMG);
  } else {
    InitTexture(imgsurface, NULL);
    SDL_FreeSurface(imgsurface);
  }
}

void aequus::video::Image::Delete() {
  DeleteTexture();
  filepath = "";
}
