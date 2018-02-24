#ifndef AEQUUS_ENTITY_SURFACE_HPP
#define AEQUUS_ENTITY_SURFACE_HPP

#include <memory>
#include "../sdl_headers.hpp"

namespace aequus {
  namespace entity {
    class Surface {
     public:
      Surface();
      Surface(const Surface& copy);
      ~Surface();

      bool LoadImage(const char* file);

      bool IsValid();

      SDL_Surface* SdlSurface();

      int w, h;

     protected:
      std::shared_ptr<SDL_Surface*> sdl_surface_;
    };
  }  // namespace entity
}  // namespace aequus

#endif /* ifndef AEQUUS_ENTITY_SURFACE_HPP */
