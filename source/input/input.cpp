#include "input/input.hpp"

#include <tuple>
#include <vector>

#include <pessum/pessum.hpp>

#include "aequus_core.hpp"
#include "sdl_headers.hpp"
#include "window/window.hpp"

namespace aequus {
  namespace input {
    std::vector<std::tuple<Uint32, Uint32, SDL_Event>> sdl_events_;
  }  // namespace input
}  // namespace aequus

void aequus::input::ParseEvent(SDL_Event event) {
  std::tuple<Uint32, Uint32, SDL_Event> entry =
      std::make_tuple(0, event.type, event);
  if (event.type == SDL_DROPFILE || event.type == SDL_DROPTEXT ||
      event.type == SDL_DROPBEGIN || event.type == SDL_DROPCOMPLETE) {
    std::get<0>(entry) = event.drop.windowID;
  } else if (event.type == SDL_KEYUP || event.type == SDL_KEYDOWN) {
    std::get<0>(entry) = event.key.windowID;
  } else if (event.type == SDL_MOUSEMOTION) {
    std::get<0>(entry) = event.motion.windowID;
  } else if (event.type == SDL_MOUSEBUTTONUP ||
             event.type == SDL_MOUSEBUTTONDOWN) {
    std::get<0>(entry) = event.button.windowID;
  } else if (event.type == SDL_MOUSEWHEEL) {
    std::get<0>(entry) = event.wheel.windowID;
  } else if (event.type == SDL_TEXTEDITING) {
    std::get<0>(entry) = event.edit.windowID;
  } else if (event.type == SDL_TEXTINPUT) {
    std::get<0>(entry) = event.text.windowID;
  } else if (event.type == SDL_USEREVENT) {
    std::get<0>(entry) = event.user.windowID;
  } else if (event.type == SDL_WINDOWEVENT) {
    std::get<0>(entry) = event.window.windowID;
  } else if (event.type == SDL_QUIT) {
    aequus_quit_ = true;
  }
  sdl_events_.push_back(entry);
  // pessum::Log(pessum::DATA, "WindowID: %i Type: %i",
  // "aequus::input::ParseEvent", std::get<0>(entry),
  // std::get<1>(entry));
}

void aequus::input::PollEvents() {
  sdl_events_.clear();
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    ParseEvent(event);
  }
}

void aequus::input::ClearEvents() { sdl_events_.clear(); }

void aequus::input::HandleEvent(window::Window& win) {
  int win_id = win.GetId();
  for (int i = 0; i < sdl_events_.size(); i++) {
    if (win_id == std::get<0>(sdl_events_[i])) {
      win.HandleEvent(std::get<1>(sdl_events_[i]), std::get<2>(sdl_events_[i]));
      sdl_events_.erase(sdl_events_.begin() + i);
    }
  }
}
