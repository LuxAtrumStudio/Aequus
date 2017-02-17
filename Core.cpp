#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 900, 900);
  aequus::video::LoadFont("resources/Roboto");
  aequus::video::LoadFont("resources/Roboto", "Title");
  aequus::video::LoadFont("resources/Roboto", "Label");
  aequus::video::fontmap["Roboto"].SetPoint(10);
  aequus::video::fontmap["Title"].SetPoint(20);
  aequus::video::fontmap["Label"].SetPoint(15);
  SDL_Renderer *ren = aequus::video::windows[0].windowrenderer.GetRenderer();
  aequus::video::Graph gra;
  gra.Init(900, 900, ren);
  gra.SetFont("Roboto");
  gra.SetTitleFont("Title");
  gra.SetLabelFont("Label");
  gra.SetGrid(0, 8, 0);
  gra.SetGrid(1, 8, 0);
  gra.SetGraphTitle("Trigonometric Function Graph");
  gra.SetAxisTitle(0, "Theta");
  gra.SetAxisTitle(1, "Amplitude");
  // gra.SetDrawAxis(true);
  // gra.SetDrawGrid(true);
  // gra.SetDrawTitle(true);
  // gra.SetDrawLabel(true);
  // gra.SetDrawEquation(true);
  gra.SetRange(0, -5, 5);
  gra.SetRange(1, -5, 5);
  // gra.SetRange(-1, 0, 100);
  // gra.SetRange(-1, 0, 50.264);
  gra.SetRange(-1, 0, 25.132);
  // gra.SetRange(-1, 0, 6.28);
  gra.Update();

  aequus::video::Plot plo, plot, plot2;

  plo.Init("1 * TAN (x(7/8))");
  // plo.Init("10");
  // plo.SetColorMap({{255, 100, 255, 255}}, false);
  plo.SetColorMap(
      {{255, 0, 0, 255}, {0, 0, 255, 255}, {0, 255, 0, 255}, {255, 0, 0, 255}},
      false);
  gra.AddPlot(plo);

  aequus::video::win->AddObject(&gra);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
