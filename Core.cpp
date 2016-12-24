#include <iostream>
#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  aequus::video::win->windowrenderer.SetColor(1, 1, 1, 1);
  aequus::video::NewObject();
  aequus::video::win->obj->CreateButton("", "pawn.png");
  aequus::video::win->obj->Scale(100, 100);
  aequus::video::NewObject();
  aequus::video::win->obj->CreateButton("", "test.png", false, false, false,
                                        100, 100);
  aequus::video::win->obj->SetPos(100, 0);
  aequus::video::NewObject();
  aequus::video::win->obj->CreateButton("", "buttons/button0.png", false, false,
                                        false, 250, 250);
  aequus::video::win->obj->SetPos(100, 100);
  while (aequus::video::AllClose() == false) {
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
