#include "aequus.h"
#include <iostream>
#include <pessum.h>

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  // aequus::video::LoadFont("resources/Roboto");
  // aequus::video::win->NewTxtObj("Hello", "Roboto");
  pessum::logging::Log();
  // aequus::video::win->NewImgObj("resources/test.png");
  pessum::logging::Log();
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
