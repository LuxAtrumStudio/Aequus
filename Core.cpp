#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::LoadFont("resources/Roboto");
  aequus::video::fontmap["Roboto"].ScaleFont("Quit", 200, 100);
  SDL_Renderer *renderer =
      aequus::video::windows[0].windowrenderer.GetRenderer();
  aequus::video::Layout lay;
  lay.Init(VERTICALLAYOUT);
  aequus::video::Text txt;
  txt.Init("Hello", "Roboto", renderer);
  lay.AddObject(txt);
  aequus::video::win->SetLayout(&lay);
  // aequus::video::win->NewButtonObj("Quit", "Roboto", "resources/Button.png");
  // aequus::video::win->objects[0]->SetStateCase(RELEASE, release);
  // aequus::video::win->NewImgObj("resources/test.png");
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
