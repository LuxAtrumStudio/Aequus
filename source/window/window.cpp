#include "window/window.hpp"

#include <memory>

#include "aequus_core.hpp"
#include "error/error.hpp"
#include "log/log.hpp"
#include "sdl_headers.hpp"
#include "types.hpp"

aequus::window::Window::Window() {}

aequus::window::Window::Window(const Window& copy)
    : title_(copy.title_),
      rect_(copy.rect_),
      clear_color_(copy.clear_color_),
      flags_(copy.flags_),
      should_close_(copy.should_close_),
      sdl_window_(copy.sdl_window_),
      sdl_renderer_(copy.sdl_renderer_) {}

aequus::window::Window::~Window() {}

void aequus::window::Window::CreateWin() { GenerateWindow(); }

void aequus::window::Window::DeleteWin() { DestroyWindow(); }

void aequus::window::Window::SetRect(Rect rect) {
  rect_ = rect;
  ChangePosition();
  ChangeSize();
}

void aequus::window::Window::SetClearColor(Color color) {
  clear_color_ = color;
}

void aequus::window::Window::SetFlags(Uint32 flags) { flags_ = flags; }

void aequus::window::Window::AddFlags(Uint32 flags) { flags_ = flags_ | flags; }

void aequus::window::Window::SetTitle(std::string title) {
  title_ = title;
  ChangeTitle();
}

std::string aequus::window::Window::GetTitle() { return title_; }

aequus::Point aequus::window::Window::GetPosition() {
  return {rect_.x, rect_.y};
}

aequus::Point aequus::window::Window::GetSize() { return {rect_.w, rect_.h}; }

aequus::Rect aequus::window::Window::GetRect() { return rect_; }

void aequus::window::Window::SetPosition(Point point) {
  rect_.x = point.x;
  rect_.y = point.y;
  ChangePosition();
}

void aequus::window::Window::Translate(Point point) {
  rect_.x += point.x;
  rect_.y += point.y;
  ChangePosition();
}

void aequus::window::Window::SetSize(Point point) {
  rect_.w = point.x;
  rect_.h = point.y;
  ChangeSize();
}

void aequus::window::Window::Scale(Point point) {
  rect_.w += point.x;
  rect_.h += point.y;
  ChangeSize();
}

Uint32 aequus::window::Window::GetId() {
  if (sdl_window_ != NULL) {
    return SDL_GetWindowID(*sdl_window_);
  } else {
    return 0;
  }
}

void aequus::window::Window::Show() {
  Clear();
  if (sdl_renderer_ != NULL) {
    SDL_RenderPresent(*sdl_renderer_);
  }
}

bool aequus::window::Window::ShouldClose() { return should_close_; }

void aequus::window::Window::SetShouldClose(bool setting) {
  should_close_ = setting;
}

void aequus::window::Window::Clear() {
  if (sdl_renderer_ != NULL) {
    SDL_SetRenderDrawColor(*sdl_renderer_, clear_color_.r, clear_color_.g,
                           clear_color_.b, clear_color_.a);
    if (SDL_RenderClear(*sdl_renderer_) != 0) {
      log::Log(log::ERROR, "Failed to clear SDL renderer",
               "aequus::window::Window::Clear");
      error::LogSdlError();
    }
  }
}

void aequus::window::Window::HandleEvent(Uint32 type, SDL_Event event) {
  if (type == SDL_WINDOWEVENT) {
    HandleWindowEvent(event.window);
  }
  if (aequus_quit_ == true) {
    should_close_ = true;
  }
}

void aequus::window::Window::GenerateWindow() {
  if (sdl_window_ == NULL) {
    sdl_window_ = std::make_shared<SDL_Window*>(SDL_CreateWindow(
        title_.c_str(), rect_.x, rect_.y, rect_.w, rect_.h, flags_));
    if (sdl_window_ == NULL) {
      log::Log(log::ERROR, "Failed to create SDL window",
               "aequus::window::Window::GenerateWindow");
      error::LogSdlError();
    } else {
      sdl_renderer_ = std::make_shared<SDL_Renderer*>(SDL_CreateRenderer(
          *sdl_window_, -1,
          SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE));
      if (sdl_renderer_ == NULL) {
        log::Log(log::ERROR, "Failed to create SDL renderer",
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
  should_close_ = false;
}

void aequus::window::Window::ChangeTitle() {
  if (sdl_window_ != NULL) {
    SDL_SetWindowTitle(*sdl_window_, title_.c_str());
  }
}

void aequus::window::Window::ChangeSize() {
  if (sdl_window_ != NULL) {
    SDL_SetWindowSize(*sdl_window_, rect_.w, rect_.h);
  }
}

void aequus::window::Window::ChangePosition() {
  if (sdl_window_ != NULL) {
    SDL_SetWindowPosition(*sdl_window_, rect_.x, rect_.y);
  }
}

void aequus::window::Window::HandleWindowEvent(SDL_WindowEvent event) {
  if (event.type == SDL_WINDOWEVENT_CLOSE) {
    should_close_ = true;
  }
}
