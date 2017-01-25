#include "../framework/framework.hpp"
#include "../log_indices.hpp"
#include "../sdl_headers.hpp"
#include "video.hpp"
#include <map>
#include <pessum.h>
#include <string>

namespace aequus {
namespace video {
std::map<std::string, Window> windowmap;
std::map<std::string, Window>::iterator winiterator;
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
  Window newwin(title, width, height, x, y, flags);
  windowmap[title] = newwin;
}

void aequus::video::UpdateAll() {
  std::map<std::string, Window>::iterator i;
  for (i = windowmap.begin(); i != windowmap.end(); ++i) {
    i->second.Display();
  }
}
