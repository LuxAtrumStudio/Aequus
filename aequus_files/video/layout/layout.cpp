#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../video_headers.hpp"
#include "layout.hpp"
#include <iostream>
#include <pessum.h>
#include <string>

void aequus::video::Layout::Init(LayoutFormat format) {
  layoutformat = format;
  if (layoutformat == HORIZONTALLAYOUT) {
    pessum::logging::Log("SUCCESS", "Created new horizontal layout",
                         "aeq/vid/lay", "Init");
  } else if (layoutformat == VERTICALLAYOUT) {
    pessum::logging::Log("SUCCESS", "Created new vertical layout",
                         "aeq/vid/lay", "Init");
  }
}

void aequus::video::Layout::Display() {
  for (int i = 0; i < sublayouts.size(); i++) {
    sublayouts[i]->Display();
  }
  for (int i = 0; i < objects.size(); i++) {
    objects[i]->Display();
  }
}

void aequus::video::Layout::AddObject(Object *obj) {
  objects.push_back(obj);
  parts.push_back(OBJ);
  ReSize();
}

void aequus::video::Layout::AddLayout(Layout *lay) {
  sublayouts.push_back(lay);
  parts.push_back(LAY);
  ReSize();
}

void aequus::video::Layout::Delete() {
  for (int i = 0; i < sublayouts.size(); i++) {
    sublayouts[i]->Delete();
  }
  for (int i = 0; i < objects.size(); i++) {
    objects[i]->Delete();
  }
  sublayouts.clear();
  objects.clear();
  parts.clear();
}

void aequus::video::Layout::SetSize(int newwidth, int newheight) {
  width = newwidth;
  height = newheight;
  ReSize();
}

void aequus::video::Layout::SetPos(int x, int y) {
  layoutx = x;
  layouty = y;
  ReSize();
}

void aequus::video::Layout::SetSizePos(int newwidth, int newheight, int x,
                                       int y) {
  width = newwidth;
  height = newheight;
  layoutx = x;
  layouty = y;
  ReSize();
}

void aequus::video::Layout::HandleEvent(SDL_Event event) {
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->type == 3) {
      Button *but = new Button();
      but = dynamic_cast<Button *>(objects[i]);
      if (but != 0) {
        but->EventCheck(event);
      }
    }
  }
  for (int i = 0; i < sublayouts.size(); i++) {
    sublayouts[i]->HandleEvent(event);
  }
}

void aequus::video::Layout::ReSize() {
  if (width != 0 && height != 0 && parts.size() > 0) {
    int objectindex = 0, layoutindex = 0;
    std::pair<int, int> elementtotal(0, 0);
    for (int i = 0; i < parts.size(); i++) {
      if (parts[i] == OBJ) {
        elementtotal.first += objects[objectindex]->GetSize().first;
        elementtotal.second += objects[objectindex]->GetSize().second;
        objectindex++;
      } else if (parts[i] == LAY) {
        if (layoutformat == HORIZONTALLAYOUT) {
          elementtotal.first += width / parts.size();
          elementtotal.second = height;
        } else if (layoutformat == VERTICALLAYOUT) {
          elementtotal.first = width;
          elementtotal.second += height / parts.size();
        }
        layoutindex++;
      }
    }
    objectindex = 0;
    layoutindex = 0;
    std::pair<double, double> elementweight(width / (double)elementtotal.first,
                                            height /
                                                (double)elementtotal.second);
    int posx = layoutx, posy = layouty;
    for (int i = 0; i < parts.size(); i++) {
      std::pair<int, int> objsize(0, 0);
      if (parts[i] == OBJ) {
        objsize = objects[objectindex]->GetSize();
      } else if (parts[i] == LAY) {
        if (layoutformat == HORIZONTALLAYOUT) {
          objsize.first = width / parts.size();
          objsize.second = height;
        } else if (layoutformat == VERTICALLAYOUT) {
          objsize.first = width;
          objsize.second = height / parts.size();
        }
      }
      std::pair<int, int> elementpos(
          (int)(objsize.first * elementweight.first),
          (int)(objsize.second * elementweight.second));
      if (layoutformat == HORIZONTALLAYOUT) {
        elementpos.second = height;
      } else if (layoutformat == VERTICALLAYOUT) {
        elementpos.first = width;
      }
      elementpos.first = (elementpos.first - objsize.first) / 2;
      elementpos.second = (elementpos.second - objsize.second) / 2;
      if (parts[i] == OBJ) {
        objects[objectindex]->SetPos(posx + elementpos.first,
                                     posy + elementpos.second);
        objectindex++;
      } else if (parts[i] == LAY) {
        sublayouts[layoutindex]->SetSizePos(objsize.first, objsize.second,
                                            posx + elementpos.first,
                                            posy + elementpos.second);
        layoutindex++;
      }
      if (layoutformat == HORIZONTALLAYOUT) {
        posx += objsize.first * elementweight.first;
      } else if (layoutformat == VERTICALLAYOUT) {
        posy += objsize.second * elementweight.second;
      }
    }
  }
}
