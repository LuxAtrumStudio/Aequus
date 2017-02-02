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
std::map<std::string, Font> fontmap;
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
    for (int j = 0; j < windows.size(); j++) {
      if (windows[j].CheckIndex(input::events[i].window.windowID) == true &&
          input::events[i].window.event == SDL_WINDOWEVENT_CLOSE) {
        windows[j].Delete();
        windows.erase(windows.begin() + j);
      }
      windows[j].HandleEvent(input::events[i]);
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

void aequus::video::LoadFont(std::string filepath, std::string mapname) {
  std::string name = "";
  if (mapname == "") {
    for (unsigned a = filepath.size() - 1; a > 0 && filepath[a] != '/'; a--) {
      name = filepath[a] + name;
    }
  } else {
    name = mapname;
  }
  Font newfont;
  newfont.Init(filepath);
  if (newfont.GoodFont() == true) {
    fontmap[name] = newfont;
  } else {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Invalid font folder",
                            LOG_AEQ_VID, "LoadFont");
  }
}

aequus::video::Font aequus::video::GetFont(std::string name) {
  std::map<std::string, Font>::iterator font;
  font = fontmap.find(name);
  if (font != fontmap.end()) {
    return (font->second);
  } else {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Font: " + name + " not initialized", LOG_AEQ_VID,
                            "GetFont");
    Font newfont;
    return (newfont);
  }
}
