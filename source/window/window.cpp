#include "window.hpp"

#include <memory>

#include <pessum/pessum.hpp>

#include "../error/error.hpp"
#include "../sdl_headers.hpp"
#include "../types.hpp"

aequus::window::Window::Window() {}

aequus::window::Window::Window(const Window& copy) {}

aequus::window::Window::~Window() {}

void aequus::window::Window::CreateWin() { GenerateWindow(); }

void aequus::window::Window::DeleteWin() { DestroyWindow(); }

void aequus::window::Window::SetRect(Rect rect) { rect_ = rect; }

void aequus::window::Window::SetClearColor(Color color) {
  clear_color_ = color;
}

void aequus::window::Window::Show() {
  Clear();
  if (sdl_renderer_ != NULL) {
    SDL_RenderPresent(*sdl_renderer_);
  }
}

void aequus::window::Window::Clear() {
  if (sdl_renderer_ != NULL) {
    SDL_SetRenderDrawColor(*sdl_renderer_, clear_color_.r, clear_color_.g,
                           clear_color_.b, clear_color_.a);
    if (SDL_RenderClear(*sdl_renderer_) != 0) {
      pessum::Log(pessum::ERROR, "Failed to clear SDL renderer",
                  "aequus::window::Window::Clear");
      error::LogSdlError();
    }
  }
}

void aequus::window::Window::GenerateWindow() {
  if (sdl_window_ == NULL) {
    sdl_window_ = std::make_shared<SDL_Window*>(SDL_CreateWindow(
        name_.c_str(), rect_.x, rect_.y, rect_.w, rect_.h, flags_));
    if (sdl_window_ == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create SDL window",
                  "aequus::window::Window::GenerateWindow");
      error::LogSdlError();
    } else {
      sdl_renderer_ = std::make_shared<SDL_Renderer*>(SDL_CreateRenderer(
          *sdl_window_, -1,
          SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE));
      if (sdl_renderer_ == NULL) {
        pessum::Log(pessum::ERROR, "Failed to create SDL renderer",
                    "aequus::window::Window::GenerateWindow");
        error::LogSdlError();
      }
    }
  }
}

void aequus::window::Window::DestroyWindow() {
  if (sdl_renderer_ != NULL && sdl_renderer_.use_count() == 1) {
    SDL_DestroyRenderer(*sdl_renderer_);
    sdl_renderer_ = NULL;
  }
  if (sdl_window_ != NULL && sdl_window_.use_count() == 1) {
    SDL_DestroyWindow(*sdl_window_);
    sdl_window_ = NULL;
  }
}
