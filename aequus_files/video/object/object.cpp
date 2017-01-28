#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "image/image.hpp"
#include "object.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Object::Init(std::string str, SDL_Renderer *renderer) {
  sdlrenderer = renderer;
  objtype = IMAGE;
  imageobj.Init(str, renderer);
}

void aequus::video::Object::Delete() {
  if (objtype == IMAGE) {
    imageobj.Delete();
  }
}

void aequus::video::Object::Display() {
  if (objtype == IMAGE) {
    imageobj.Display();
  }
}
