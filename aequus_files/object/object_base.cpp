#include <pessum.h>
#include "../aequus_core.hpp"
#include "../sdl_extention/rect.hpp"
#include "object_base.hpp"

aequus::ObjectBase::ObjectBase() {}

aequus::ObjectBase::~ObjectBase() {
  if (sdl_texture != NULL) {
    SDL_DestroyTexture(sdl_texture);
    sdl_texture = NULL;
  }
  if (sdl_surface != NULL) {
    SDL_FreeSurface(sdl_surface);
    sdl_surface = NULL;
  }
}

int aequus::ObjectBase::Type() { return (AEQ_OBJ_NONE); }

void aequus::ObjectBase::Display() {
  if (sdl_texture != NULL) {
    if (SDL_RenderCopyEx(sdl_renderer, sdl_texture, sdl_source_rect,
                         sdl_dest_rect, rotate_angle, sdl_rotate_point,
                         sdl_renderer_flip) != 0) {
      pessum::Log(pessum::ERROR, "Failed to copy texture to renderer",
                  "aequus/ObjectBase/Display");
      SdlError(SDL);
    }
  }
}

void aequus::ObjectBase::CreateSdlTexture() {
  if (sdl_surface == NULL) {
    pessum::Log(pessum::WARNING, "No SDL surface created",
                "aequus/ObjectBase/CreateSdlTexture");
  } else if (sdl_renderer == NULL) {
    pessum::Log(pessum::WARNING, "NO SDL renderer created",
                "aequus/ObjectBase/CreateSdlTexture");
  } else {
    if (sdl_texture != NULL) {
      SDL_DestroyTexture(sdl_texture);
      sdl_texture = NULL;
    }
    sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);
    if (sdl_texture == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create texture from surface",
                  "aequus/ObjectBase/CreateSdlTexture");
      SdlError(SDL);
    } else {
      sdl_base_size = Make_Rect(0, 0, sdl_surface->w, sdl_surface->h);
      sdl_dest_rect = Make_Rect(0, 0, sdl_surface->w, sdl_surface->h);
      sdl_source_rect = Make_Rect(0, 0, sdl_surface->w, sdl_surface->h);
      sdl_rotate_point = Make_Point(sdl_surface->w / 2, sdl_surface->h / 2);
    }
  }
}
