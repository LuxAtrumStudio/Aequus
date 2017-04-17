#ifndef AEQUUS_WINDOW_HPP
#define AEQUUS_WINDOW_HPP
#include <string>
#include "../sdl_headers.hpp"
namespace aequus {
  class Window {
   public:
    void CreateWindow(std::string name, int width, int height,
                      int x_pos = SDL_WINDOWPOS_CENTERED,
                      int y_pos = SDL_WINDOWPOS_CENTERED, Uint32 flags = 0);
    void DeleteWindow();
    void Display();
    void Clear();
    SDL_Window* SdlWindow();
    SDL_Renderer* SdlRenderer();

   private:
    int sdl_window_id = 0;
    SDL_Window* sdl_window = NULL;
    SDL_Renderer* sdl_renderer = NULL;
  };
}
#endif
