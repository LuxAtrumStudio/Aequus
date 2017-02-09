#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  double pi = 3.141592;
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::Canvas newcanvas;
  SDL_Renderer *ren = aequus::video::windows[0].windowrenderer.GetRenderer();
  newcanvas.Init(500, 500, ren);
  newcanvas.DrawArc(50, 50, 50, 50, 0, pi);
  newcanvas.DrawEllipse(150, 50, 50, 50);
  newcanvas.DrawLine(200, 0, 300, 100);
  newcanvas.DrawPoint(350, 50);
  newcanvas.DrawQuad(4, 400 + rand() % 100, rand() % 100, 400 + rand() % 100,
                     rand() % 100, 400 + rand() % 100, rand() % 100,
                     400 + rand() % 100, rand() % 100);
  newcanvas.DrawRect(0, 100, 100, 100);
  newcanvas.DrawRect(100, 100, 100, 100, 1, 25, 30, 40);
  newcanvas.DrawTriangle(250, 100, 300, 200, 200, 200);
  newcanvas.Update();
  aequus::video::windows[0].AddObject(&newcanvas);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
