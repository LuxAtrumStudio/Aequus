#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "spacer.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Spacer::Init(int w, int h) {
  width = w;
  height = h;
  // Scale(width, height);
  type = 4;
}
void aequus::video::Spacer::Delete() { width = 0, height = 0; }
