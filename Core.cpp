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
  aequus::video::Graph gra;
  gra.Init(500, 500, ren);
  gra.SetFont("Roboto");
  gra.SetTitleFont("Title");
  gra.SetLabelFont("Label");
  gra.SetGrid(0, 8, 0);
  gra.SetGrid(1, 8, 0);
  gra.SetGraphTitle("Trigonometric Function Graph");
  gra.SetAxisTitle(0, "Theta");
  gra.SetAxisTitle(1, "Amplitude");
  gra.SetDrawAxis(true);
  gra.SetDrawGrid(true);
  gra.SetDrawTitle(true);
  gra.SetDrawLabel(true);
  gra.SetDrawEquation(true);
  gra.SetRange(0, 0, 6.2830);
  gra.SetRange(1, -1, 1);
  gra.Update();

  aequus::video::Plot plo, plot, plot2;

  plo.Init("SIN x");
  plo.SetColorMap({{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}}, true);
  plot.Init("COS x");
  plot.SetColorMap({{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}},
                   true);
  plot2.Init("TAN x");
  plot2.SetColorMap({{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}},
                    true);

  gra.AddPlot(plo);
  gra.AddPlot(plot);
  gra.AddPlot(plot2);

  aequus::video::win->AddObject(&gra);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
