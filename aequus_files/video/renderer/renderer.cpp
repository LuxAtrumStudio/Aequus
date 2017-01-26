#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../window/window.hpp"
#include "renderer.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Renderer::Init(SDL_Window *sdlwindow, Uint32 flags,
                                   std::string name) {
  windowname = name;
  sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, flags);
  if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to create renderer for: " + windowname, AVR,
                            "Renderer");
    framework::GetSdlError(framework::SDL);
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "Created renderer for: " + windowname, AVR,
                            "Renderer");
  }
}

void aequus::video::Renderer::Delete() {
  SDL_DestroyRenderer(sdlrenderer);
  sdlrenderer = NULL;
}

void aequus::video::Renderer::Display() {
  if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to display renderer", AVR, "Display");
  } else {
    SDL_RenderPresent(sdlrenderer);
  }
}

void aequus::video::Renderer::Clear() {
  if (SDL_RenderClear(sdlrenderer) != 0) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to clear renderer",
                            AVR, "Clear");
    framework::GetSdlError(framework::SDL);
  }
}
