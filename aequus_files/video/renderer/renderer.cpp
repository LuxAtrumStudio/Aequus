#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../window/window.hpp"
#include "renderer.hpp"
#include <pessum.h>
#include <string>

aequus::video::Renderer::Renderer(SDL_Window *sdlwindow, Uint32 flags,
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

aequus::video::Renderer::Renderer() { sdlrenderer = NULL; }

aequus::video::Renderer::~Renderer() {
  SDL_DestroyRenderer(sdlrenderer);
  pessum::logging::LogLoc(pessum::logging::SUCCESS,
                          "Destroyed renderer for: " + windowname, AVR,
                          "~Renderer");
}

void aequus::video::Renderer::Display() { SDL_RenderPresent(sdlrenderer); }
