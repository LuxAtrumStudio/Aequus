#ifndef AEQUUS_OBJECT_IMAGE_HPP
#define AEQUUS_OBJECT_IMAGE_HPP
#include <string>
#include "../../sdl_headers.hpp"
#include "../object_base.hpp"
namespace aequus {
  class Image : public ObjectBase {
   public:
    Image();
    Image(SDL_Renderer* renderer);
    Image(std::string path);
    Image(std::string path, SDL_Renderer* renderer);
    ~Image();
    void SetFile(std::string path);
    void SetRenderer(SDL_Renderer* renderer);
    int Type();

   private:
    std::string file_path;
  };
}
#endif
