#ifndef VIDEO_WINDOW_WINDOW_HPP
#define VIDEO_WINDOW_WINDOW_HPP
#include "../../sdl_headers.hpp"
#include "../layout/layout.hpp"
#include "../object/button/button.hpp"
#include "../object/object.hpp"
#include "../renderer/renderer.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
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
  ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI,
  MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
  WINDOWED = 0
};
enum WindowPositionFlags {
  CENTERED = SDL_WINDOWPOS_CENTERED,
  CENTERED_MASK = SDL_WINDOWPOS_CENTERED_MASK,
  UNDEFINED = SDL_WINDOWPOS_UNDEFINED,
  UNDEFINED_MASK = SDL_WINDOWPOS_UNDEFINED_MASK
};
class Window {
public:
  std::vector<Object *> objects;
  Layout *windowlayout = NULL;
  Renderer windowrenderer;
  void Init(std::string title, int width, int height,
            WindowPositionFlags x = CENTERED, WindowPositionFlags y = CENTERED,
            Uint32 flags = WINDOWED);
  void Delete();
  void Display();
  bool CheckIndex(int index);
  std::string GetName();
  void HandleEvent(SDL_Event sdlevent);
  void SetLayout(Layout *layout);
  void AddObject(Object *obj);
  void NewImgObj(std::string str);
  void NewTxtObj(std::string str, std::string font);
  void NewButtonObj(std::string str, std::string font, std::string img,
                    int width = -1, int height = -1);

private:
  std::string windowname = "";
  int windowwidth = 100, windowheight = 100;
  int windowx = 0, windowy = 0;
  SDL_Window *sdlwindow = NULL;
  int sdlwindowid = 0;
  int currentobj = 0;
};
}
}
#endif
