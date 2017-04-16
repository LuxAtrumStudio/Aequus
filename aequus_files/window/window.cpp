#include <pessum.h>
#include <string>
#include "../aequus_core.hpp"
#include "../sdl_headers.hpp"
#include "window.hpp"

void aequus::Window::CreateWindow(std::string name, int width, int height,
                                  int x, int y, Uint32 flags) {
  if (sdl_window == NULL) {
    sdl_window = SDL_CreateWindow(name.c_str(), x, y, width, height, flags);
    if (sdl_window == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create SDL window",
                  "aequus/Window/CreateWindow");
      SdlError(SDL);
    } else {
      SDL_GetWindowSurface(sdl_window);
      if (sdl_renderer == NULL) {
        sdl_renderer =
            SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED |
                                                   SDL_RENDERER_TARGETTEXTURE);
        if (sdl_renderer == NULL) {
          pessum::Log(pessum::ERROR, "Failed to create SDL renderer",
                      "aequus/Window/CreateWindow");
          SdlError(SDL);
        }
      } else {
        pessum::Log(pessum::WARNING, "SDL renderer already created",
                    "aequus/Window/CreateWindow");
      }
      sdl_window_id = SDL_GetWindowID(sdl_window);
    }
  } else {
    pessum::Log(pessum::WARNING, "SDL window already created",
                "aequus/Window/CreateWindow");
  }
}

void aequus::Window::DeleteWindow() {
  if (sdl_renderer != NULL) {
    SDL_DestroyRenderer(sdl_renderer);
    sdl_renderer = NULL;
  } else {
    pessum::Log(pessum::WARNING, "No SDL renderer created",
                "aequus/Window/DeleteWindow");
  }
  if (sdl_window != NULL) {
    SDL_DestroyWindow(sdl_window);
    sdl_window = NULL;
  } else {
    pessum::Log(pessum::WARNING, "No SDL window created",
                "aequus/Window/DeleteWindow");
  }
}

void aequus::Window::Display() {
  Clear();
  if (sdl_renderer != NULL) {
    SDL_RenderPresent(sdl_renderer);
  } else {
    pessum::Log(pessum::WARNING, "No SDL renderer created",
                "aequus/Window/Display");
  }
}

void aequus::Window::Clear() {
  if (sdl_renderer != NULL) {
    if (SDL_RenderClear(sdl_renderer) != 0) {
      pessum::Log(pessum::ERROR, "Failed to clear SDL renderer",
                  "aequus/Window/Clear");
      SdlError(SDL);
    }
  } else {
    pessum::Log(pessum::WARNING, "No SDL renderer created",
                "aequus/Window/Clear");
  }
}
