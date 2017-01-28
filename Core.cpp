#include "aequus.h"
#include <iostream>
#include <pessum.h>

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::win->NewObj("no.png");
  // aequus::video::win->objects[0].imageobj.Scale(2.0, 2.0);
  // double angle = 0;
  int x = 245, y = 245;
  aequus::video::win->objects[0].imageobj.SetPos(x, y);
  while (aequus::video::AllClose() == false) {
    // aequus::video::win->objects[0].imageobj.Rotate(angle);
    // aequus::video::win->objects[0].imageobj.SetPos(x, y);
    aequus::Frame();
    // angle += 0.01;
  }
  aequus::TerminateAequus();
  return (1);
}
