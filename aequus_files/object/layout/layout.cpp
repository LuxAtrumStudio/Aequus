#include <pessum.h>
#include "../object.hpp"
#include "../object_base.hpp"
#include "layout.hpp"
#include "../../sdl_extention/rect.hpp"


aequus::Layout::Layout() {
  sdl_dest_rect = Make_Rect(0, 0, 0, 0);
}

aequus::Layout::Layout(int w, int h){
  sdl_dest_rect = Make_Rect(0, 0, w, h);
}

aequus::Layout::Layout(int type) { format = type;
  sdl_dest_rect = Make_Rect(0, 0, 0, 0);
}

aequus::Layout::Layout(int type, int w, int h){
  format = type;
  sdl_dest_rect = Make_Rect(0, 0, w, h);
}

aequus::Layout::~Layout() {}

void aequus::Layout::SetFormat(int type) { format = type; 
  ReformatObjects();
}

int aequus::Layout::Type() { return (AEQ_OBJ_LAYOUT); }

void aequus::Layout::Display() {
  for (int i = 0; i < sub_objects.size(); i++) {
    sub_objects[i].Display();
  }
}

void aequus::Layout::AddObject(Object obj) {
  sub_objects.push_back(obj);
  //ReformatObjects();
}

int aequus::Layout::GetFormat() { return (format); }

int aequus::Layout::Size() { return (sub_objects.size()); }

void aequus::Layout::ReformatObjects() {
  if (format == AEQ_OBJ_LAY_FREE) {
  } else if (format == AEQ_OBJ_LAY_VERTICAL) {
  } else if (format == AEQ_OBJ_LAY_VERTICAL_FORCE) {
    int total_height = 0;
    for (int i = 0; i < sub_objects.size(); i++) {
      if (sub_objects[i].ptr->GetSize()->w > sdl_dest_rect->w) {
        sub_objects[i].ptr->Scale(sdl_dest_rect->w, false);
      }
      total_height += sub_objects[i].ptr->GetSize()->h;
    }
    double scale_factor = 0.0;
    if (total_height > sdl_dest_rect->h) {
      scale_factor = (double)(total_height - sdl_dest_rect->h) /
                     (double)(sdl_dest_rect->h);
      scale_factor = 1.0 - scale_factor;
    } else {
      scale_factor = 1;
    }
    total_height = 0;
    for (int i = 0; i < sub_objects.size() && scale_factor != 1; i++) {
      sub_objects[i].ptr->Scale(scale_factor);
      total_height += sub_objects[i].ptr->GetSize()->h;
    }
    int spacing = (sdl_dest_rect->h - total_height) / (sub_objects.size() + 1);
    int current_x = sdl_dest_rect->x, current_y = sdl_dest_rect->y + spacing;
    for (int i = 0; i < sub_objects.size(); i++) {
      current_x = (sdl_dest_rect->w - sub_objects[i].ptr->GetSize()->w) / 2;
      sub_objects[i].ptr->Translate(current_x, current_y);
      current_y += sub_objects[i].ptr->GetSize()->h + spacing;
    }
  }else if(format == AEQ_OBJ_LAY_HORIZONTAL){
  
  }else if(format == AEQ_OBJ_LAY_HORIZONTAL_FORCE){ 
    int total_width = 0;
    for (int i = 0; i < sub_objects.size(); i++) {
      if (sub_objects[i].ptr->GetSize()->h > sdl_dest_rect->h) {
        //sub_objects[i].ptr->Scale(sdl_dest_rect->h, true);
      }
      total_width += sub_objects[i].ptr->GetSize()->w;
    }
    double scale_factor = 0.0;
    if (total_width > sdl_dest_rect->w) {
      pessum::Log(pessum::DATA, "%i", "", total_width);
      
      scale_factor = (double)(total_width) / (double)(sdl_dest_rect->w);
      //scale_factor = (double)(total_width - sdl_dest_rect->w) /
      //               (double)(sdl_dest_rect->w);
      pessum::Log(pessum::DATA, "%f", "", scale_factor);
      scale_factor = 1.0 / scale_factor;
      pessum::Log(pessum::DATA, "%f", "", scale_factor);
    } else {
      scale_factor = 1;
    }
    total_width = 0;
    for (int i = 0; i < sub_objects.size() && scale_factor != 1; i++) {
      sub_objects[i].ptr->Scale(scale_factor);
      total_width += sub_objects[i].ptr->GetSize()->w;
    }
    int spacing = (sdl_dest_rect->w - total_width) / (sub_objects.size() + 1);
    int current_x = sdl_dest_rect->x + spacing, current_y = sdl_dest_rect->y;
    for (int i = 0; i < sub_objects.size(); i++) {
      current_y = (sdl_dest_rect->h - sub_objects[i].ptr->GetSize()->h) / 2;
      sub_objects[i].ptr->Translate(current_x, current_y);
      current_x += sub_objects[i].ptr->GetSize()->w + spacing;
    }
  }
}
