#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "spacer.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Spacer::Init(int w, int h, bool resize) {
  width = w;
  height = h;
  resizeable = resize;
  Scale(width, height);
}

void aequus::video::Spacer::Resize(int w, int h) {
  if (resizeable == true) {
    width = w;
    height = h;
    Scale(width, height);
  }
}

void aequus::video::Spacer::Delete() { width = 0, height = 0; }
