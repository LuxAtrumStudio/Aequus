#include "../framework/framework.hpp"
#include "../input/input.hpp"
#include "../log_indices.hpp"
#include "../sdl_headers.hpp"
#include "video_headers.hpp"
#include <map>
#include <pessum.h>
#include <string>

namespace aequus {
namespace video {
std::vector<Window> windows;
Window *win = NULL;
int winindex = 0;
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
  Window newwin;
  newwin.Init(title, width, height, x, y, flags);
  windows.push_back(newwin);
  winindex = windows.size() - 1;
  win = &windows[windows.size() - 1];
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
            windows[j].Delete();
            windows.erase(windows.begin() + j);
          }
        }
      }
    }
  }
}

void aequus::video::DeleteWindows() {
  for (int i = 0; i < windows.size(); i++) {
    windows[i].Delete();
  }
  windows.clear();
}

int aequus::video::GetIndex(std::string name) {
  for (int i = 0; i < windows.size(); i++) {
    if (windows[i].GetName() == name) {
      return (i);
    }
  }
  return (0);
}
