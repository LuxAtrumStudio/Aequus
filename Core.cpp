#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::LoadFont("resources/Roboto");
  SDL_Renderer *ren = aequus::video::windows[0].windowrenderer.GetRenderer();
  aequus::video::Graph gra;
  gra.Init(300, 300, ren);
  gra.AddPlot("2 MUL TAN x");
  aequus::video::win->AddObject(&gra);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
