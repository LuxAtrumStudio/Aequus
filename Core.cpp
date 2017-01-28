#include "aequus.h"
#include <iostream>
#include <pessum.h>

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::Font newfont;
  newfont.Init("resources/Roboto");
  newfont.GetFont(aequus::video::BOLD);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
