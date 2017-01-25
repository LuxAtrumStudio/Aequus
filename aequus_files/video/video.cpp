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
std::map<std::string, Window> windowmap;
std::vector<Window> windows;
}
}

bool aequus::video::AllClose() {
  if (windowmap.size() != 0) {
    return (false);
  } else {
    return (true);
  }
}

void aequus::video::NewWindow(std::string title, int width, int height,
                              WindowPositionFlags x, WindowPositionFlags y,
                              Uint32 flags) {
  windowmap[title] = Window(title, width, height, x, y, flags);
}

void aequus::video::UpdateAll() {
  std::map<std::string, Window>::iterator i;
  for (i = windowmap.begin(); i != windowmap.end(); ++i) {
    i->second.Display();
  }
}

void aequus::video::HandleEvents() {
  for (int i = 0; i < input::events.size(); i++) {
    if (input::events[i].type == SDL_WINDOWEVENT) {
      std::map<std::string, Window>::iterator j;
      for (j = windowmap.begin(); j != windowmap.end(); ++j) {
        if (j->second.CheckIndex(input::events[i].window.windowID) == true) {
          if (input::events[i].window.event != SDL_WINDOWEVENT_CLOSE) {
            j->second.HandleEvent(input::events[i]);
          } else if (input::events[i].window.event == SDL_WINDOWEVENT_CLOSE) {
            windowmap.erase(j);
          }
        }
      }
    }
  }
}

void aequus::video::DeleteWindows() { windowmap.clear(); }
