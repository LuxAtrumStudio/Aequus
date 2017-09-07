#include "entity/image.hpp"
#include "entity/surface.hpp"

#include <memory>

#include "sdl_headers.hpp"

aequus::Image::Image() {}

aequus::Image::Image(const char* file) {
  sdl_surface_ = std::make_shared<SDL_Surface*>(IMG_Load(file));
}

aequus::Image::Image(const Image& copy) {}

aequus::Image::~Image() {}
