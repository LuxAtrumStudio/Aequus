#include "entity/surface.hpp"

#include "error/error.hpp"
#include "log/log.hpp"
#include "sdl_headers.hpp"
#include "types.hpp"

aequus::entity::Surface::Surface() {}

aequus::entity::Surface::Surface(const Surface& copy)
    : w(copy.w), h(copy.h), sdl_surface_(copy.sdl_surface_) {}

aequus::entity::Surface::~Surface() {
  if (sdl_surface_.use_count() == 1 && *sdl_surface_ != NULL) {
    SDL_FreeSurface(*sdl_surface_);
  }
  sdl_surface_ = NULL;
}

bool aequus::entity::Surface::IsValid() {
  return (sdl_surface_ != NULL && *sdl_surface_ != NULL);
}

SDL_Surface* aequus::entity::Surface::SdlSurface() {
  if (IsValid() == true) {
    return *sdl_surface_;
  } else {
    return NULL;
  }
}
