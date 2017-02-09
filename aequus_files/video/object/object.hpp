#ifndef VIDEO_OBJECT_OBJECT_HPP
#define VIDEO_OBJECT_OBJECT_HPP
#include "../../sdl_headers.hpp"
#include "../video_enums.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
enum RenderFlip { NOFLIP = 0, HORIZONTAL = 1, VERITCAL = 2 };
class Object {
public:
  int type = 0;
  virtual void Dummy() {}
  void SetRenderer(SDL_Renderer *renderer = NULL);
  void SetColorMod(std::vector<int> colors);
  void SetColorMod(std::vector<double> colors);
  void SetBlendMode(BlendMode mode);
  void Rotate(double theta);
  void Rotate(int degree);
  void Flip(RenderFlip renderflip);
  void SetRotatePoint(int x, int y);
  void SetRotatePoint(double x, double y);
  void SetSourceRect(std::vector<int> rect);
  void SetSourceRect(std::vector<double> rect);
  void SetDestRect(std::vector<int> rect);
  void SetDestRect(std::vector<double> rect);
  void Scale(int scaledwidth, int scaledheight);
  void Scale(double scaledwidth, double scaledheight);
  void SetPos(int x, int y);
  void UpdateTexture();
  std::pair<int, int> GetSize();
  void Display();

  virtual void Delete();
  SDL_Texture *sdltexture = NULL;
  SDL_Surface *sdlsurface = NULL;

protected:
  void InitTexture(SDL_Surface *surface = NULL, SDL_Renderer *renderer = NULL);
  void DeleteTexture();
  int width = 0, height = 0, posx = 0, posy = 0, rotatex = 0, rotatey = 0,
      scalewidth = 0, scaleheight = 0;
  double angle = 0;
  BlendMode blend = NONE;
  RenderFlip flip = NOFLIP;
  std::vector<int> sourcerect = {0, 0, 0, 0}, destrect = {0, 0, 0, 0},
                   colormod = {255, 255, 255, 255};

  SDL_RendererFlip sdlflip = SDL_FLIP_NONE;
  SDL_BlendMode sdlblend = SDL_BLENDMODE_NONE;
  SDL_Point *sdlrotate = NULL;
  SDL_Rect *sdlsourcerect = NULL, *sdldestrect = NULL;
  SDL_Renderer *sdlrenderer = NULL;
};
}
}
#endif
