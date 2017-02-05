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
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "Created new horizontal layout", LOG_AEQ_VID_LAY,
                            "Init");
  } else if (layoutformat == VERTICALLAYOUT) {
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "Created new vertical layout", LOG_AEQ_VID_LAY,
                            "Init");
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
    int iwidth = 0, iheight = 0;
    int xpos = layoutx, ypos = layouty;
    if (layoutformat == HORIZONTALLAYOUT) {
      iheight = height;
      iwidth = width / parts.size();
    } else if (layoutformat == VERTICALLAYOUT) {
      iwidth = width;
      iheight = height / parts.size();
    }
    int objindex = 0;
    int layoutindex = 0;
    for (int i = 0; i < parts.size(); i++) {
      if (parts[i] == OBJ) {
        int objwidth, objheight;
        std::pair<int, int> objsize = objects[objindex]->GetSize();
        objwidth = objsize.first;
        objheight = objsize.second;
        int objposx = (iwidth - objwidth) / 2,
            objposy = (iheight - objheight) / 2;
        objects[objindex]->SetPos(objposx + xpos, objposy + ypos);
        objindex++;
      } else if (parts[i] == LAY) {
        sublayouts[layoutindex]->SetSize(iwidth, iheight);
        sublayouts[layoutindex]->SetPos(xpos, ypos);
        layoutindex++;
      }
      if (layoutformat == HORIZONTALLAYOUT) {
        xpos += iwidth;
      } else if (layoutformat == VERTICALLAYOUT) {
        ypos += iheight;
      }
    }
  }
}
