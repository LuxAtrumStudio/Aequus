#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  aequus::video::NewAdvObject();
  std::string eqs;
  for (int i = 0; i < 10; i++) {
    eqs += "x * " + std::to_string(i);
    // eqs += "x - " + std::to_string(i);
    if (i != 9) {
      eqs += ",";
    }
  }
  aequus::video::win->advobj->CreateGraph(eqs, aequus::video::AdvObject::PLOT,
                                          500, 500, true, true, true, true,
                                          true, true, true, -10, 10);
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
