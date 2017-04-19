#include <pessum.h>
#include <vector>
#include "../sdl_headers.hpp"
#include "input.hpp"

namespace aequus {
  std::vector<SDL_Event> sdl_events;
}

void aequus::PollEvents() {
  sdl_events.clear();
  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event) != 0) {
    sdl_events.push_back(sdl_event);
  }
}

SDL_Event aequus::GetEvent(int type) {
  SDL_Event event;
  event.type = -1;
  bool found = false;
  if (type == -1 && sdl_events.size() > 0) {
    event = sdl_events.back();
    found = true;
  }
  for (int i = sdl_events.size() - 1 && found == false; i >= 0; i--) {
    if (sdl_events[i].type == type) {
      event = sdl_events[i];
      found = true;
    }
  }
  return (event);
}
