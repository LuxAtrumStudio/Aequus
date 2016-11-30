#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  aequus::video::NewAdvObject();
  aequus::video::win->advobj->CreateGraph(
      "4 * ( x ^ 0.5 ) - 3", aequus::video::AdvObject::PLOT, 500, 500, true,
      true, true, true, true, true, 0, 10);
  aequus::video::NewObject();
  aequus::video::win->obj->CreateImgObj("back_arrow.png");
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
    if (aequus::input::events.size() > 0) {
      if (aequus::input::events[0].type == aequus::input::KEYBOARD) {
        aequus::video::TerminateWindow();
      }
    }
  }
  aequus::framework::TerminateSdl();
  pessum::TerminatePessumComponents();
  return (1);
}
