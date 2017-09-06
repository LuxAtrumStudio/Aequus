#ifndef AEQUUS_ENTITY_TEXTURE_HPP
#define AEQUUS_ENTITY_TEXTURE_HPP

#include <memory>

#include "../sdl_headers.hpp"

namespace aequus {
  class Texture {
   public:
    Texture();
    Texture(const Texture& copy);
    ~Texture();

    bool IsValid();

   private:
    std::shared_ptr<SDL_Texture*> sdl_texture_ = NULL;
  };
}  // namespace aequus

#endif /* ifndef AEQUUS_ENTITY_TEXTURE_HPP */
