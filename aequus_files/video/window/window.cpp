#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../renderer/renderer.hpp"
#include "window.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Window::Init(std::string title, int width, int height,
                                 WindowPositionFlags x, WindowPositionFlags y,
                                 Uint32 flags) {
  windowname = title;
  windowwidth = width;
  windowheight = height;
  windowx = x;
  windowy = y;
  sdlwindow = SDL_CreateWindow(windowname.c_str(), windowx, windowy,
                               windowwidth, windowheight, flags);
  if (sdlwindow == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Unable to create SDL window:  " + windowname, AVW,
                            "Window");
    framework::GetSdlError(framework::SDL);
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "Created SDL window: " + windowname, AVW, "Window");
    SDL_GetWindowSurface(sdlwindow);
    windowrenderer.Init(sdlwindow, ACCELERATED | TARGETTEXTURE, windowname);
    sdlwindowid = SDL_GetWindowID(sdlwindow);
  }
}

void aequus::video::Window::Delete() {
  objects.clear();
  SDL_DestroyWindow(sdlwindow);
  windowrenderer.Delete();
  pessum::logging::LogLoc(pessum::logging::SUCCESS,
                          "Terminated SDL window: " + windowname, AVW,
                          "~Window");
  windowname = "";
  windowwidth = 0;
  windowheight = 0;
  windowx = 0;
  windowy = 0;
  sdlwindowid = 0;
}

void aequus::video::Window::Display() {
  windowrenderer.Clear();
  windowrenderer.Display();
}

bool aequus::video::Window::CheckIndex(int index) {
  if (index == sdlwindowid) {
    return (true);
  } else {
    return (false);
  }
}

std::string aequus::video::Window::GetName() { return (windowname); }

void aequus::video::Window::HandleEvent(SDL_Event sdlevent) {}
