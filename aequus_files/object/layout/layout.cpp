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

void aequus::Layout::SetFormat(int type) { format = type; }

int aequus::Layout::Type() { return (AEQ_OBJ_LAYOUT); }

void aequus::Layout::Display() {
  ReformatObjects();
  for (int i = 0; i < sub_objects.size(); i++) {
    sub_objects[i].Display();
  }
}

void aequus::Layout::AddObject(Object obj) { sub_objects.push_back(obj); }

int aequus::Layout::GetFormat() { return (format); }

int aequus::Layout::Size() { return (sub_objects.size()); }

void aequus::Layout::ReformatObjects(){
  if(format == AEQ_OBJ_LAY_FREE){
    
  }else if(format == AEQ_OBJ_LAY_VERTICAL){
    
  }else if(format == AEQ_OBJ_LAY_VERTICAL_FORCE){
    int width = sdl_dest_rect->w;
    int height = sdl_dest_rect->h;
    int space = 0;
    int sub_object_height = 0;
    for (int i = 0; i < sub_objects.size(); i++) {
       if(sub_objects[i].ptr->GetSize()->w > width){
        sub_objects[i].ptr->Scale(width);
      }
       sub_object_height += sub_objects[i].ptr->GetSize()->h;
    }
    if(height > sub_object_height){
      space = (height - sub_object_height) / (sub_objects.size() + 1);
    }
    int current_x = sdl_dest_rect->x;
    int current_y = sdl_dest_rect->y + space;
    int obj_width = 0;
    int obj_height = 0;
    double scale_factor = (double)height / (double)sub_object_height;
    if(scale_factor > 1){
      scale_factor = 1;
    }
    for (int i = 0; i < sub_objects.size(); i++) {
      SDL_Rect* sub_obj_rect = sub_objects[i].ptr->GetSize();
      current_x = (width - sub_obj_rect->w) / 2;
      obj_width = sub_obj_rect->w;
      obj_height = scale_factor * sub_obj_rect->h;
      sub_objects[i].ptr->SetDestRect(current_x, current_y, obj_width,
                                      obj_height);
      current_y += obj_height + space;
    }
  }else if(format == AEQ_OBJ_LAY_HORIZONTAL){
  
  }else if(format == AEQ_OBJ_LAY_HORIZONTAL_FORCE){
  
  }
}
