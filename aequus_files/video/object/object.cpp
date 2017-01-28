#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "image/image.hpp"
#include "object.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Object::InitImg(std::string str, SDL_Renderer *renderer) {
  sdlrenderer = renderer;
  objtype = IMAGE;
  imageobj.Init(str, renderer);
}

void aequus::video::Object::InitTxt(std::string text, std::string fontname,
                                    SDL_Renderer *renderer) {
  sdlrenderer = renderer;
  objtype = TEXT;
  textobj.Init(text, fontname, renderer);
}

void aequus::video::Object::Delete() {
  if (objtype == IMAGE) {
    imageobj.Delete();
  }
  if (objtype == TEXT) {
    textobj.Delete();
  }
}

void aequus::video::Object::Display() {
  if (objtype == IMAGE) {
    imageobj.Display();
  }
  if (objtype == TEXT) {
    textobj.Display();
  }
}
