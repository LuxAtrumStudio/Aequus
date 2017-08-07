#ifndef AEQUUS_WINDOW_WINDOW_HPP
#define AEQUUS_WINDOW_WINDOW_HPP

#include <memory>

#include "../sdl_headers.hpp"
#include "../types.hpp"

namespace aequus {
  namespace window {
    class Window {
     public:
      Window();
      Window(const Window& copy);
      ~Window();

      void CreateWin();
      void DeleteWin();

      void SetRect(Rect rect);
      void SetClearColor(Color color);

      void Show();

      void Clear();

     private:
      void GenerateWindow();
      void DestroyWindow();

      std::string name_ = "Aequus";
      Rect rect_ = {0, 0, 0, 0};
      Color clear_color_ = {0, 0, 0, 255};

      Uint32 flags_ = 0;

      std::shared_ptr<SDL_Window*> sdl_window_ = NULL;
      std::shared_ptr<SDL_Renderer*> sdl_renderer_ = NULL;
    };
  }  // namespace window
}  // namespace aequus

#endif /* ifndef AEQUUS_WINDOW_WINDOW_HPP */
