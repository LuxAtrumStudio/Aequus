#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  bool updategraph = true;
  std::string eqstr = "x", laststr = "x";
  aequus::video::NewAdvObject();
  aequus::video::win->advobj->CreateGraph("x", aequus::video::AdvObject::PLOT,
                                          500, 500, true, true, true, true,
                                          true, true, true, "TEST", -10, 10);
  aequus::video::NewAdvObject();
  aequus::video::win->advobj->CreateTextBox(500, 50, "white.png", false, false,
                                            "x");
  while (aequus::video::AllClose() == false) {
    if (updategraph == true) {
      std::cout << eqstr << "\n";
      aequus::video::win->advobjects[0].UpdateGraph(eqstr);
      aequus::video::win->advobjects[0].SetPos(0, 100);
      updategraph = false;
      laststr = eqstr;
    }
    eqstr = aequus::video::win->advobjects[1].GetString();
    if (eqstr != "" && eqstr != laststr) {
      updategraph = true;
    }
    aequus::Frame();
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
