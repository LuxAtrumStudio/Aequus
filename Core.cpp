#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::LoadFont("resources/Roboto");
  aequus::video::fontmap["Roboto"].ScaleFont("Quit", 300, 100);
  SDL_Renderer *renderer =
      aequus::video::windows[0].windowrenderer.GetRenderer();
  aequus::video::Layout lay;
  lay.Init(VERTICALLAYOUT);
  // aequus::video::Text txt;
  // txt.Init("Hello", "Roboto", renderer);
  // lay.AddObject(txt);
  aequus::video::Button *btt = new aequus::video::Button();
  btt->Init("Quit", "Roboto", "resources/Button.png", renderer, 300, 100);
  btt->SetStateCase(RELEASE, release);
  aequus::video::Button *btt1 = new aequus::video::Button();
  btt1->Init("Quit", "Roboto", "resources/Button.png", renderer, 300, 100);
  btt1->SetStateCase(RELEASE, release);
  aequus::video::Button *btt2 = new aequus::video::Button();
  btt2->Init("HELLO", "Roboto", "resources/Button.png", renderer, 300, 100);
  btt2->SetStateCase(RELEASE, release);
  lay.AddObject(btt);
  lay.AddObject(btt1);
  lay.AddObject(btt2);
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
