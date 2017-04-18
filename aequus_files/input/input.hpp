#ifndef AEQUUS_INPUT_HPP
#define AEQUUS_INPUT_HPP
#include <vector>
#include "../sdl_headers.hpp"
namespace aequus {
  extern std::vector<SDL_Event> sdl_events;
  void PollEvents();
  SDL_Event GetEvent(int type = -1);
}
#endif
