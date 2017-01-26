#ifndef VIDEO_OBJECT_SUFRACE_SURFACE_HPP
#define VIDEO_OBJECT_SUFRACE_SURFACE_HPP
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Object::Surface : public Object {
public:
  Surface(std::string filepath);
  ~Surface();
  SDL_Surface *sdlsurface = NULL;
  void SetSourceRect(std::vector<int> rect = {-1, -1, -1, -1});
  void SetSourceRect(std::vector<double> rect = {1, 1, 1, 1});
  void SetDestRect(std::vector<int> rect = {-1, -1, -1, -1});
  void SetDestRect(std::vector<double> rect = {1, 1, 1, 1});
  void SetColorMod(std::vector<int> mod = {255, 255, 255, 255});
  void SetColorMod(std::vector<double> mod = {1, 1, 1, 1});
  void Scale(int newwidth, int newheight);
  void Scale(double newwidth, double newheight);
  void SetBlendMode(int mode);
  std::vector<int> GetSourceRect();
  std::vector<int> GetDestRect();

private:
  std::string imagepath = "";
  std::vector<int> sourcerect = {0, 0, 0, 0}, destrect = {0, 0, 0, 0},
                   colormod = {255, 255, 255, 255};
};
}
}
#endif
