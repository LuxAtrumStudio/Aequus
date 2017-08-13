#ifndef AEQUUS_IMAGE_IMAGE_HPP
#define AEQUUS_IMAGE_IMAGE_HPP

#include <memory>
#include <string>

#include "../object/object.hpp"
#include "../sdl_headers.hpp"

namespace aequus {
  namespace image {
    class Image : public object::Object {
     public:
      Image();
      Image(const Image& copy);
      Image(std::shared_ptr<SDL_Renderer*> renderer);
      Image(std::string path);
      Image(std::string path, std::shared_ptr<SDL_Renderer*> renderer);
      ~Image();

      void SetFile(std::string path);

     private:
      std::string image_path_;
    };
  }  // namespace image
}  // namespace aequus

#endif /* ifndef AEQUUS_IMAGE_IMAGE_HPP */
