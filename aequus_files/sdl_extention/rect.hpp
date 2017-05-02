#ifndef AEQUUS_SDL_EXTENTION_RECT_HPP
#define AEQUUS_SDL_EXTENTION_RECT_HPP
#include "../sdl_headers.hpp"
namespace aequus {
  SDL_Point* Make_Point(int x, int y);
  SDL_Rect* Make_Rect(int x, int y, int w, int h);
}
#endif
