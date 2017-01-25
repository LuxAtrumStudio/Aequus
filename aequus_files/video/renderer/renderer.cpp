#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "renderer.hpp"
#include <pessum.h>
#include <string>

aequus::video::Renderer::Renderer(SDL_Window *sdlwindow, Uint32 flags) {
  sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, flags);
  if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to create renderer",
                            AVR, "Renderer");
    framework::GetSdlError(framework::SDL);
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS, "Created renderer", AVR,
                            "Renderer");
  }
}

aequus::video::Renderer::Renderer() { sdlrenderer = NULL; }

aequus::video::Renderer::~Renderer() {
  SDL_DestroyRenderer(sdlrenderer);
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Destroyed renderer", AVR,
                          "~Renderer");
}

void aequus::video::Renderer::Display() { SDL_RenderPresent(sdlrenderer); }
