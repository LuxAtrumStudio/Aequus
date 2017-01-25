#include "../framework/framework.hpp"
#include "../input/input.hpp"
#include "../log_indices.hpp"
#include "../sdl_headers.hpp"
#include "video.hpp"
#include <map>
#include <pessum.h>
#include <string>

namespace aequus {
namespace video {
std::vector<Window> windows;
}
}

bool aequus::video::AllClose() {
  if (windows.size() != 0) {
    return (false);
  } else {
    return (true);
  }
}

void aequus::video::NewWindow(std::string title, int width, int height,
                              WindowPositionFlags x, WindowPositionFlags y,
                              Uint32 flags) {
  windows.push_back(Window(title, width, height, x, y, flags));
}

void aequus::video::UpdateAll() {
  for (int i = 0; i < windows.size(); i++) {
    windows[i].Display();
  }
}

void aequus::video::HandleEvents() {
  for (int i = 0; i < input::events.size(); i++) {
    if (input::events[i].type == SDL_WINDOWEVENT) {
      for (int j = 0; j < windows.size(); j++) {
        if (windows[j].CheckIndex(input::events[i].window.windowID) == true) {
          if (input::events[i].window.event != SDL_WINDOWEVENT_CLOSE) {
            windows[j].HandleEvent(input::events[i]);
          } else if (input::events[i].window.event == SDL_WINDOWEVENT_CLOSE) {
            windows.erase(windows.begin() + j);
          }
        }
      }
    }
  }
}

void aequus::video::DeleteWindows() { windows.clear(); }
