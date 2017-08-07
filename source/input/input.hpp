#ifndef AEQUUS_INPUT_INPUT_HPP
#define AEQUUS_INPUT_INPUT_HPP

#include <vector>

#include "../sdl_headers.hpp"
#include "../window/window.hpp"

namespace aequus {
  namespace input {
    void ParseEvent(SDL_Event event);
    void PollEvents();
    void ClearEvents();
    void HandleEvent(window::Window& win);
    SDL_Event GetEvent(int type = -1);
  }  // namespace input
}  // namespace aequus

#endif /* ifndef AEQUUS_INPUT_INPUT_HPP */
