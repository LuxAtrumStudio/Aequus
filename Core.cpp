#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::LoadFont("resources/Roboto");
  aequus::video::LoadFont("resources/Roboto", "Title");
  aequus::video::LoadFont("resources/Roboto", "Label");
  aequus::video::fontmap["Roboto"].SetPoint(10);
  aequus::video::fontmap["Title"].SetPoint(20);
  aequus::video::fontmap["Label"].SetPoint(15);
  SDL_Renderer *ren = aequus::video::windows[0].windowrenderer.GetRenderer();
  // SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  aequus::video::Graph gra;
  gra.Init(300, 300, ren);
  gra.SetFont("Roboto");
  gra.SetTitleFont("Title");
  gra.SetLabelFont("Label");
  gra.SetGrid(0, 9, 1);
  gra.SetGrid(1, 9, 1);
  gra.SetGraphTitle("Test Graph");
  gra.SetDrawAxis(true);
  gra.SetDrawGrid(true);
  gra.SetDrawTitle(true);
  gra.SetDrawLabel(true);
  gra.Update();
  aequus::video::win->AddObject(&gra);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
