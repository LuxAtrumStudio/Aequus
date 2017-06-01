#include <pessum.h>
#include "../../sdl_extention/rect.hpp"
#include "../object.hpp"
#include "layout.hpp"

aequus::Layout::Layout() { 
  sdl_base_size = Make_Rect(0,0,0,0);
  sdl_dest_rect = Make_Rect(0, 0, 0, 0); }

aequus::Layout::Layout(int w, int h) { 
  sdl_base_size = Make_Rect(0,0,w,h);
  sdl_dest_rect = Make_Rect(0, 0, w, h); }

aequus::Layout::Layout(int type) {
  format = type;
  sdl_base_size = Make_Rect(0,0,0,0);
  sdl_dest_rect = Make_Rect(0, 0, 0, 0);
}

aequus::Layout::Layout(int type, int w, int h) {
  format = type;
  sdl_base_size = Make_Rect(0,0,w,h);
  sdl_dest_rect = Make_Rect(0, 0, w, h);
}

aequus::Layout::~Layout() {}

void aequus::Layout::SetFormat(int type) {
  format = type;
  ReformatObjects();
}

int aequus::Layout::Type() { return (AEQ_OBJ_LAYOUT); }

void aequus::Layout::Display() {
  for (int i = 0; i < sub_objects.size(); i++) {
    if(sub_objects[i]->Type() == AEQ_OBJ_LAYOUT){
      std::shared_ptr<Layout> layout_object= std::dynamic_pointer_cast<Layout>(sub_objects[i]); 
      layout_object->Display();
    }else{
      sub_objects[i]->Display();
    }
  }
}

void aequus::Layout::AddObject(std::shared_ptr<ObjectBase> obj) {
  sub_objects.push_back(obj);
  ReformatObjects();
}

int aequus::Layout::GetFormat() { return (format); }

int aequus::Layout::Size() { return (sub_objects.size()); }

void aequus::Layout::ReformatObjects() {
  if (format == AEQ_OBJ_LAY_FREE) {
  } else if (format == AEQ_OBJ_LAY_VERTICAL) {
  } else if (format == AEQ_OBJ_LAY_VERTICAL_FORCE) {
    int total_height = 0;
    for (int i = 0; i < sub_objects.size(); i++) {
      if(sub_objects[i]->Type() != AEQ_OBJ_LAYOUT){
        if (sub_objects[i]->GetSize()->w > sdl_dest_rect->w) {
          sub_objects[i]->Scale(sdl_dest_rect->w, false);
        }
        total_height += sub_objects[i]->GetSize()->h;
      }else{
        total_height += sdl_dest_rect->h / sub_objects.size();
        sub_objects[i]->Scale(sdl_dest_rect->w, (int)(sdl_dest_rect->h / sub_objects.size()));
      }
    }
    double scale_factor = 0.0;
    if (total_height > sdl_dest_rect->h) {
      scale_factor = (double)(total_height - sdl_dest_rect->h) /
                     (double)(sdl_dest_rect->h);
      scale_factor = 1.0 - scale_factor;
    } else {
      scale_factor = 1;
    }
    if(scale_factor != 1){
      total_height = 0;
    }
    for (int i = 0; i < sub_objects.size() && scale_factor != 1; i++) {
      sub_objects[i]->Scale(scale_factor);
      total_height += sub_objects[i]->GetSize()->h;
    }
    int spacing = (float)(sdl_dest_rect->h - total_height) / (float)(sub_objects.size() + 1);
    int current_x = sdl_dest_rect->x, current_y = sdl_dest_rect->y + spacing;
    for (int i = 0; i < sub_objects.size(); i++) {
      current_x = (sdl_dest_rect->w - sub_objects[i]->GetSize()->w) / 2;
      sub_objects[i]->Translate(current_x, current_y);
      if(sub_objects[i]->Type() == AEQ_OBJ_LAYOUT){
        std::shared_ptr<Layout> layout_object= std::dynamic_pointer_cast<Layout>(sub_objects[i]); 
        layout_object->ReformatObjects();
        sub_objects[i] = layout_object;
      }
      current_y += sub_objects[i]->GetSize()->h + spacing;
    }
  } else if (format == AEQ_OBJ_LAY_HORIZONTAL) {
  } else if (format == AEQ_OBJ_LAY_HORIZONTAL_FORCE) {
    int total_width = 0;
    for (int i = 0; i < sub_objects.size(); i++) {
      if(sub_objects[i]->Type() != AEQ_OBJ_LAYOUT){
        if (sub_objects[i]->GetSize()->h > sdl_dest_rect->h) {
          sub_objects[i]->Scale(sdl_dest_rect->h, true);
        }
        total_width += sub_objects[i]->GetSize()->w;
      }else{
        total_width = sdl_dest_rect->w / sub_objects.size();
        sub_objects[i]->Scale(sdl_dest_rect->w / sub_objects.size(), sdl_dest_rect->h);
      }
    }
    double scale_factor = 0.0;
    if (total_width > sdl_dest_rect->w) {
      scale_factor = (double)(total_width - sdl_dest_rect->w) / (double)(sdl_dest_rect->w);
      scale_factor = 1.0 / scale_factor;
    } else {
      scale_factor = 1;
    }
    if(scale_factor != 1){
      total_width = 0;
    }
    for (int i = 0; i < sub_objects.size() && scale_factor != 1; i++) {
      sub_objects[i]->Scale(scale_factor);
      total_width += sub_objects[i]->GetSize()->w;
    }
    int spacing = (float)(sdl_dest_rect->w - total_width) / (float)(sub_objects.size() + 1);
    int current_x = sdl_dest_rect->x + spacing, current_y = sdl_dest_rect->y;
    for (int i = 0; i < sub_objects.size(); i++) {
      current_y = sdl_dest_rect->y + (sdl_dest_rect->h - sub_objects[i]->GetSize()->h) / 2;
      sub_objects[i]->Translate(current_x, current_y);
      if(sub_objects[i]->Type() == AEQ_OBJ_LAYOUT){
        std::shared_ptr<Layout> layout_object = std::dynamic_pointer_cast<Layout>(sub_objects[i]);
        layout_object->ReformatObjects();
        sub_objects[i] = layout_object;
      }
      current_x += sub_objects[i]->GetSize()->w + spacing;
    }
  }
}
