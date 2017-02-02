#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../video_headers.hpp"
#include <map>
#include <pessum.h>
#include <stdarg.h>
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
  for (int i = 0; i < objects.size(); i++) {
    objects[i]->Display();
  }
  windowlayout->Display();
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

void aequus::video::Window::HandleEvent(SDL_Event sdlevent) {
  for (int i = 0; i < objects.size(); i++) {
    pessum::logging::Log();
    Button *b = new Button();
    b = dynamic_cast<Button *>(objects[i]);
    pessum::logging::Log();
    if (b != 0) {
      // std::cout << "downcast from b1 to d successful\n";
      b->EventCheck(sdlevent); // safe to call
    }
    pessum::logging::Log();
  }
}

void aequus::video::Window::SetLayout(Layout *layout) {
  if (windowlayout != NULL) {
    windowlayout->Delete();
  }
  windowlayout = layout;
  windowlayout->SetSize(windowwidth, windowheight);
}

void aequus::video::Window::NewImgObj(std::string str) {
  Image *newimg = new Image();
  newimg->Init(str, windowrenderer.GetRenderer());
  objects.push_back(newimg);
  currentobj = objects.size() - 1;
}

void aequus::video::Window::NewTxtObj(std::string str, std::string font) {
  Text *newtxt = new Text();
  newtxt->Init(str, font, windowrenderer.GetRenderer());
  objects.push_back(newtxt);
  currentobj = objects.size() - 1;
}

void aequus::video::Window::NewButtonObj(std::string str, std::string font,
                                         std::string img, int width,
                                         int height) {
  // Button newbutton;
  Button *newbutton = new Button();
  newbutton->Init(str, font, img, windowrenderer.GetRenderer(), width, height);
  // newbutton.Init(str, font, img, windowrenderer.GetRenderer(), width,
  // height);
  objects.push_back(newbutton);
  currentobj = objects.size() - 1;
}
