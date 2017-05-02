#ifndef AEQUUS_WINDOW_HPP
#define AEQUUS_WINDOW_HPP
#include <string>
#include "../object/layout/layout_headers.hpp"
#include "../sdl_headers.hpp"
namespace aequus {
  class Window {
   public:
    Window();
    ~Window();
    Window(std::string name, int width, int height,
           int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED,
           Uint32 flags = 0);
    Window(const Window& copy_win);
    void CreateWindow(std::string name, int width, int height,
                      int x = SDL_WINDOWPOS_CENTERED,
                      int y = SDL_WINDOWPOS_CENTERED, Uint32 flags = 0);
    void DeleteWindow();
    void Display();
    void Clear();
    void AddObject(Object obj);
    SDL_Window* SdlWindow();
    SDL_Renderer* SdlRenderer();

    std::string window_name;
    Layout window_base_layout = Layout(AEQ_OBJ_LAY_FREE);

   private:
    int sdl_window_id = 0;
    std::pair<int, int> window_size;
    SDL_Window* sdl_window = NULL;
    SDL_Renderer* sdl_renderer = NULL;
  };
}
#endif
