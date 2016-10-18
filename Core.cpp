#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  aequus::video::AdvObject adv;
  adv.InitalizeAdvObj();
  adv.CreateGraph("test.lux", 100, 100,
                  aequus::video::win->windowrenderer.sdlrenderer);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::framework::TerminateSdl();
  pessum::TerminatePessumComponents();
  return (1);
}
