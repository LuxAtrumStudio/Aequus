#include "../aequus_core.hpp"
#include "../framework/framework.hpp"
#include "../log_indices.hpp"
#include "../sdl_headers.hpp"
#include "input.hpp"
#include <pessum.h>
#include <string>

namespace aequus {
namespace input {
std::vector<SDL_Event> events;
}
}

void aequus::input::PollEvents() {
  SDL_Event sdlevent;
  events.clear();
  while (SDL_PollEvent(&sdlevent) != 0) {
    if (sdlevent.type == SDL_QUIT) {
      QuitState = true;
    } else {
      events.push_back(sdlevent);
    }
  }
}
