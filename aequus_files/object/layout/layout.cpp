#include <pessum.h>
#include "../object.hpp"
#include "../object_base.hpp"
#include "layout.hpp"

aequus::Layout::Layout() {}

aequus::Layout::Layout(int type) { format = type; }

aequus::Layout::~Layout() {}

void aequus::Layout::SetFormat(int type) { format = type; }

int aequus::Layout::Type() { return (AEQ_OBJ_LAYOUT); }

void aequus::Layout::Display() {
  if(format == AEQ_OBJ_LAY_FREE){
    for (int i = 0; i < sub_objects.size(); i++) {
      sub_objects[i].Display();
    }
  }else if(format == AEQ_OBJ_LAY_HORIZONTAL){
    int sub_objects_width = 0;
    int sub_objects_height = 0;
    for(int i = 0; i < sub_objects.size(); i++){
      sub_objects_width += sub_objects[i].ptr->GetSize()->w;
    }
    int space = 0;
    if(sub_objects_width < sdl_dest_rect->w){
      space = (sdl_dest_rect->w - sub_objects_width) / (sub_objects.size() + 1);
    }
    int current_pos_x = sdl_dest_rect->x, current_pos_y = sdl_dest_rect->h;
    for(int i = 0; i < sub_objects.size(); i++){
      sub_objects[i].ptr->Translate(current_pos_x, current_pos_y);
      current_pos_x += sub_objects[i].ptr->GetSize()->w + space;
    }
  }
}

void aequus::Layout::AddObject(Object obj) { sub_objects.push_back(obj); }

int aequus::Layout::GetFormat() { return (format); }

int aequus::Layout::Size() { return (sub_objects.size()); }
