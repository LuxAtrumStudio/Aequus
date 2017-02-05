#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::LoadFont("resources/Roboto");
  aequus::video::fontmap["Roboto"].ScaleFont("1", 160, 160);
  SDL_Renderer *renderer =
      aequus::video::windows[0].windowrenderer.GetRenderer();
  aequus::video::Text txt1;
  txt1.Init("1", "Roboto", renderer);
  aequus::video::Text txt2;
  txt2.Init("2", "Roboto", renderer);
  aequus::video::Text txt3;
  txt3.Init("3", "Roboto", renderer);
  aequus::video::Text txt4;
  txt4.Init("4", "Roboto", renderer);
  aequus::video::Text txt5;
  txt5.Init("5", "Roboto", renderer);
  aequus::video::Text txt6;
  txt6.Init("6", "Roboto", renderer);

  aequus::video::Layout lay1, lay2, lay3, mainlay;
  lay1.Init(HORIZONTALLAYOUT);
  lay1.AddObject(&txt1);
  lay1.AddObject(&txt2);
  lay1.AddObject(&txt3);
  lay2.Init(HORIZONTALLAYOUT);
  lay2.AddObject(&txt4);
  lay3.Init(HORIZONTALLAYOUT);
  lay3.AddObject(&txt5);
  lay3.AddObject(&txt6);
  mainlay.Init(VERTICALLAYOUT);
  mainlay.AddLayout(&lay1);
  mainlay.AddLayout(&lay2);
  mainlay.AddLayout(&lay3);
  aequus::video::win->SetLayout(&mainlay);
  // aequus::video::win->NewButtonObj("Quit", "Roboto", "resources/Button.png");
  // aequus::video::win->objects[0]->SetStateCase(RELEASE, release);
  // aequus::video::win->NewImgObj("resources/test.png");
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
