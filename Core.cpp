#include <iostream>
#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  while (aequus::video::AllClose() == false) {
    aequus::video::NewObject();
    aequus::video::win->obj->CreateTextObj(std::to_string(rand()), 12, 1, 1, 1,
                                           1);
    aequus::Frame();
    aequus::video::win->obj->TerminateObject();
    aequus::video::win->objects.clear();
    if (aequus::input::events.size() > 0) {
      if (aequus::input::events[0].type == aequus::input::KEYBOARD &&
          aequus::input::events[0].key == 113) {
        aequus::video::TerminateWindow();
      }
    }
  }
  aequus::framework::TerminateSdl();
  pessum::TerminatePessumComponents();
  return (1);
}
