#include "image/image.hpp"

#include <memory>
#include <string>

#include "error/error.hpp"
#include "log/log.hpp"
#include "object/object.hpp"
#include "sdl_headers.hpp"

aequus::image::Image::Image() : image_path_(std::string()) {}

aequus::image::Image::Image(const Image& copy)
    : image_path_(copy.image_path_) {}

aequus::image::Image::Image(std::shared_ptr<SDL_Renderer*> renderer)
    : Object(renderer) {}

aequus::image::Image::Image(std::string path) : image_path_(path) {
  sdl_surface_ = std::make_shared<SDL_Surface*>(IMG_Load(image_path_.c_str()));
  if (*sdl_surface_ == NULL) {
    log::Log(log::ERROR, "Failed to load image from file \"%s\"",
             "aequus::image::Image::Image", image_path_.c_str());
    error::LogImgError();
  }
}

aequus::image::Image::Image(std::string path,
                            std::shared_ptr<SDL_Renderer*> renderer)
    : Object(renderer), image_path_(path) {
  sdl_surface_ = std::make_shared<SDL_Surface*>(IMG_Load(image_path_.c_str()));
  if (*sdl_surface_ == NULL) {
    log::Log(log::ERROR, "Failed to load image from file \"%s\"",
             "aequus::image::Image::Image", image_path_.c_str());
    error::LogImgError();
    sdl_surface_ = NULL;
  } else {
    CreateTexture();
  }
}

aequus::image::Image::~Image() {}

void aequus::image::Image::SetFile(std::string path) {
  image_path_ = path;
  sdl_surface_ = std::make_shared<SDL_Surface*>(IMG_Load(image_path_.c_str()));
  if (*sdl_surface_ == NULL) {
    log::Log(log::ERROR, "Failed to load image from file \"%s\"",
             "aequus::image::Image::SetFile", image_path_.c_str());
    error::LogImgError();
    sdl_surface_ = NULL;
  } else {
    CreateTexture();
  }
}
