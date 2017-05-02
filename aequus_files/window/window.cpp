#include <pessum.h>
#include <string>
#include "../aequus_core.hpp"
#include "../sdl_headers.hpp"
#include "window.hpp"

aequus::Window::Window() {}

aequus::Window::~Window() {}

aequus::Window::Window(std::string name, int width, int height, int x, int y,
                       Uint32 flags) {
  window_name = name;
  if (sdl_window == NULL) {
    sdl_window = SDL_CreateWindow(name.c_str(), x, y, width, height, flags);
    if (sdl_window == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create SDL window",
                  "aequus/Window/CreateWindow");
      SdlError(SDL);
    } else {
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
      window_size = std::make_pair(width, height);
      window_base_layout = Layout(AEQ_OBJ_LAY_FREE, width, height);
    }
  } else {
    pessum::Log(pessum::WARNING, "SDL window already created",
                "aequus/Window/CreateWindow");
  }
}

aequus::Window::Window(const Window& copy_win) {
  window_name = copy_win.window_name;
  window_base_layout = copy_win.window_base_layout;
  sdl_window = copy_win.sdl_window;
  sdl_renderer = copy_win.sdl_renderer;
  window_size = copy_win.window_size;
}

void aequus::Window::CreateWindow(std::string name, int width, int height,
                                  int x, int y, Uint32 flags) {
  window_name = name;
  if (sdl_window == NULL) {
    sdl_window = SDL_CreateWindow(name.c_str(), x, y, width, height, flags);
    if (sdl_window == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create SDL window",
                  "aequus/Window/CreateWindow");
      SdlError(SDL);
    } else {
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
      window_size = std::make_pair(width, height);
      window_base_layout = Layout(AEQ_OBJ_LAY_FREE, width, height);
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
  window_base_layout.Display();
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

void aequus::Window::AddObject(Object obj) {
  window_base_layout.AddObject(obj);
}

SDL_Window* aequus::Window::SdlWindow() { return (sdl_window); }

SDL_Renderer* aequus::Window::SdlRenderer() { return (sdl_renderer); }
