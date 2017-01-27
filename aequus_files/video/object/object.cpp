#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "object_headers.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Object::Init(std::string str, SDL_Renderer *renderer) {
  sdlrenderer = renderer;
  objtype = TEXTURE;
  objtexture.Init(str, sdlrenderer);
}

void aequus::video::Object::Delete() {}

void aequus::video::Object::Display() {
  if (objtype == TEXTURE) {
    objtexture.Display();
  }
}
