#include <stdarg.h>
#include "object.hpp"
#include "object_base.hpp"
#include "object_headers.hpp"

aequus::Object::Object() {}

aequus::Object::Object(int type) {
  if (type == AEQ_OBJ_LAYOUT) {
    ptr = std::make_shared<Layout>(Layout());
  } else if (type == AEQ_OBJ_IMAGE) {
    ptr = std::make_shared<Image>(Image());
  }
}

aequus::Object::Object(int type, SDL_Renderer* renderer) {
  if (type == AEQ_OBJ_LAYOUT) {
    ptr = std::make_shared<Layout>(Layout());
  } else if (type == AEQ_OBJ_IMAGE) {
    ptr = std::make_shared<Image>(Image(renderer));
  }
}

aequus::Object::Object(int type, std::string str, SDL_Renderer* renderer) {
  if (type == AEQ_OBJ_LAYOUT) {
    ptr = std::make_shared<Layout>(Layout());
  } else if (type == AEQ_OBJ_IMAGE) {
    ptr = std::make_shared<Image>(Image(str, renderer));
  }
}

aequus::Object::~Object() { ptr = NULL; }

int aequus::Object::Type() { return (ptr->Type()); }

void aequus::Object::Display() { ptr->Display(); }
