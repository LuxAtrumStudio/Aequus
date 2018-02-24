#include "entity/image.hpp"
#include "entity/surface.hpp"

#include <memory>

#include "log/log.hpp"
#include "sdl_headers.hpp"

aequus::Image::Image() {}

aequus::Image::Image(const char* file) {
  sdl_surface_ = std::make_shared<SDL_Surface*>(IMG_Load(file));
  if (IsValid() == true) {
    log::Log(log::SUCCESS, "Surface is valid at creation");
  } else {
    log::Log(log::FATAL, "Surface is invalid at creation");
  }
}

aequus::Image::Image(const Image& copy) {}

aequus::Image::~Image() {}
