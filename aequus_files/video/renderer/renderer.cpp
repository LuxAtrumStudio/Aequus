#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../video_headers.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Renderer::Init(SDL_Window *sdlwindow, Uint32 flags,
                                   std::string name) {
  windowname = name;
  sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, flags);
  if (sdlrenderer == NULL) {
    pessum::logging::Log("ERROR",
                         "Failed to create renderer for: " + windowname,
                         "aeq/vid/ren", "Renderer");
    framework::GetSdlError(framework::SDL);
  } else {
    pessum::logging::Log("SUCCESS", "Created renderer for: " + windowname,
                         "aeq/vid/ren", "Renderer");
  }
}

void aequus::video::Renderer::Delete() {
  SDL_DestroyRenderer(sdlrenderer);
  sdlrenderer = NULL;
}

void aequus::video::Renderer::Display() {
  if (sdlrenderer == NULL) {
    pessum::logging::Log("ERROR", "Failed to display renderer", "aeq/vid/ren",
                         "Display");
  } else {
    SDL_RenderPresent(sdlrenderer);
  }
}

void aequus::video::Renderer::Clear() {
  if (SDL_RenderClear(sdlrenderer) != 0) {
    pessum::logging::Log("ERROR", "Failed to clear renderer", "aeq/vid/ren",
                         "Clear");
    framework::GetSdlError(framework::SDL);
  }
}

SDL_Renderer *aequus::video::Renderer::GetRenderer() { return (sdlrenderer); }
