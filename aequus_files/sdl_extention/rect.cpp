#include "../sdl_headers.hpp"
#include "rect.hpp"

SDL_Point* aequus::Make_Point(int x, int y) {
  SDL_Point* point = new SDL_Point();
  point->x = x;
  point->y = y;
  return (point);
}
SDL_Rect* aequus::Make_Rect(int x, int y, int w, int h) {
  SDL_Rect* rect = new SDL_Rect();
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
  return (rect);
}
