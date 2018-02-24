#ifndef AEQUUS_ENTITY_TEXTURE_HPP
#define AEQUUS_ENTITY_TEXTURE_HPP

#include <memory>

#include "../sdl_headers.hpp"
#include "../types.hpp"
#include "surface.hpp"

namespace aequus {
  namespace entity {
    enum BlendMode {
      BLENDMODE_NONE,
      BLENDMODE_BLEND,
      BLENDMODE_ADD,
      BLENDMODE_MOD
    };

    class Texture {
     public:
      Texture();
      Texture(const Texture& copy);
      Texture(Surface surface_);
      ~Texture();

      void SetSurface(Surface surface_);

      void CreateTexture();
      void DeleteTexture();

      void SetBlendMode(unsigned int blend_mode);
      void SetColorMod(Color color_mod);

      bool IsValid();

      SDL_Texture* SdlTexture();

      Surface surface;

     private:
      void GenerateTexture();
      void DestroyTexture();

      unsigned int blend_mode_;
      Color color_mod_;

      std::shared_ptr<SDL_Texture*> sdl_texture_ = NULL;
    };
  }  // namespace entity
}  // namespace aequus

#endif /* ifndef AEQUUS_ENTITY_TEXTURE_HPP */
