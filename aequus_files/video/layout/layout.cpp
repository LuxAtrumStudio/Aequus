#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../video_headers.hpp"
#include "layout.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Layout::Init(LayoutFormat format) { layoutformat = format; }

void aequus::video::Layout::Display() {}

void aequus::video::Layout::AddObject(Object obj) {}

void aequus::video::Layout::AddLayout(Layout lay) {}

void aequus::video::Layout::Delete() {}

void aequus::video::Layout::SetSize(int newwidth, int newheight) {
  width = newwidth;
  height = newheight;
  ReSize();
}
