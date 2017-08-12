#ifndef AEQUUS_WINDOW_WINDOW_HPP
#define AEQUUS_WINDOW_WINDOW_HPP

#include <memory>

#include "../sdl_headers.hpp"
#include "../types.hpp"

namespace aequus {
  namespace window {
    enum WindowFlags {
      FULLSCREEN = SDL_WINDOW_FULLSCREEN,
      FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
      OPENGL = SDL_WINDOW_OPENGL,
      SHOWN = SDL_WINDOW_SHOWN,
      HIDDEN = SDL_WINDOW_HIDDEN,
      BORDERLESS = SDL_WINDOW_BORDERLESS,
      RESIZABLE = SDL_WINDOW_RESIZABLE,
      MINIMIZED = SDL_WINDOW_MINIMIZED,
      MAXIMIZED = SDL_WINDOW_MAXIMIZED,
      INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
      INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
      MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
      FOREIGN = SDL_WINDOW_FOREIGN,
      ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI
      // MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
      // ALWAYS_ON_TOP = SDL_WINDOW_ALWAYS_ON_TOP,
      // UTILITY = SDL_WINDOW_UTILITY,
      // TOOLTIP = SDL_WINDOW_TOOLTIP,
      // POPUP_MENU = SDL_WINDOW_POPUP_MENU
    };

    class Window {
     public:
      Window();
      Window(const Window& copy);
      ~Window();

      void CreateWin();
      void DeleteWin();

      void SetRect(Rect rect);
      void SetClearColor(Color color);
      void SetFlags(Uint32 flags);
      void AddFlags(Uint32 flags);
      void SetTitle(std::string title);
      std::string GetTitle();

      Point GetPosition();
      Point GetSize();
      Rect GetRect();

      void SetPosition(Point point);
      void Translate(Point point);

      void SetSize(Point point);
      void Scale(Point point);

      Uint32 GetId();

      bool ShouldClose();
      void SetShouldClose(bool setting);

      void Show();

      void Clear();

      void HandleEvent(Uint32 type, SDL_Event event);

     private:
      void GenerateWindow();
      void DestroyWindow();

      void ChangeTitle();
      void ChangeSize();
      void ChangePosition();

      void HandleWindowEvent(SDL_WindowEvent event);

      std::string title_ = "Aequus";
      Rect rect_ = {0, 0, 0, 0};
      Color clear_color_ = {0, 0, 0, 255};

      Uint32 flags_ = 0;
      bool should_close_ = false;

      std::shared_ptr<SDL_Window*> sdl_window_ = NULL;
      std::shared_ptr<SDL_Renderer*> sdl_renderer_ = NULL;
    };
  }  // namespace window
}  // namespace aequus

#endif /* ifndef AEQUUS_WINDOW_WINDOW_HPP */
