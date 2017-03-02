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
    pessum::logging::Log("ERROR", "Failed to load image file: " + filepath,
                         "aeq/vid/obj/img", "Init");
    framework::GetSdlError(framework::IMG);
  } else {
    InitTexture(imgsurface, renderer);
  }
  type = 1;
}

void aequus::video::Image::UpdateFile(std::string img) {
  filepath = img;
  SDL_Surface *imgsurface = IMG_Load(filepath.c_str());
  if (imgsurface == NULL) {
    pessum::logging::Log("ERROR", "Failed to load image file: " + filepath,
                         "aeq/vid/obj/img", "Init");
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
